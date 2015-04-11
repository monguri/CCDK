#include "vce.h"
#include "vcecommon.h"
#include "osdep.h"
#include "core.h"

/* each element stored in an array */
typedef struct _entry_t {
    int use;
    struct _entry_t *next , *prev;   /* link to used list */
    char *buf;
} entry_t;

/* array that stores many entry_t */
typedef struct _array_t {
    int use;
    int num;
    size_t size;        /* size of structure */

    entry_t *ent;       /* body */

    /* store freed entries in stack (could be used as used list at the same time)*/
    entry_t **blank_pointer_stack;
    int blank_pointer_stack_pointer;

    /* pointer to master buffer that is allocated by malloc */
    char *master_buffer;
    size_t master_buffer_size;

    /* pointer to the first element of used list. Indicates nothing is in use if NULL */
    entry_t *inuse_top_pointer;
    /* pointer to the last element of used list. Indicates nothing is in use if NULL */
    entry_t *inuse_last_pointer;

    /* name of this array, for logging */
    char name[32];

} array_t;

/* All array_t is stored in this array. Total size is fixed in the initialization */
static array_t *array_table;



#define CHECKINDEX(i) ( (i) < 0 || (i) >= vce_limit.max_array || array_table == NULL )


int vce_array_init_world(void) {
    if( vce_limit.max_array > 0 ){
        array_table = (array_t*)VCEMALLOC( sizeof(array_t)*vce_limit.max_array);
        if( !array_table ){
            return SET_LAST_ERROR(VCE_EMEM);
        }
        memset( array_table, 0, sizeof(array_t)*vce_limit.max_array);
    }
    return SET_LAST_ERROR(0);
}
int vce_array_fin_world(void) {
    if( array_table ){
        VCEFREE(array_table);
        array_table = NULL;
    }
    return SET_LAST_ERROR(0);
}

int vce_init_array( size_t size , int num , const char *nm ) {
    int i;
    int index = -1;

    /* Linear search is OK because array initialization is not often */
    for(i=0;i<vce_limit.max_array; i++){
        if(array_table[i].use == 0 ){
            index = i;
            break;
        }
    }
    if( index == -1 ){
        VCE_ERROUT_V0( FATAL_ARRAY_SCARCE );
        return SET_LAST_ERROR(VCE_EFULL);
    }

    if( size == 0 ) return SET_LAST_ERROR(VCE_EINVAL);

    /* allocate master buffer */
    if( ( array_table[index].master_buffer =
          (char *) VCEMALLOC( size * num ) ) == NULL ) {
        VCE_ERROUT_V1( FATAL_ARRAY_FMALLOC_D , index );
        return SET_LAST_ERROR(VCE_EFULL);
    }
    /* allocate entry list */
    if( ( array_table[index].ent =
          (entry_t * ) VCEMALLOC( sizeof( entry_t ) * num ) ) == NULL ) {
        VCE_ERROUT_V1( FATAL_ARRAY_FMALLOC1_D ,index );
        VCEFREE( array_table[index].master_buffer );
        return SET_LAST_ERROR(VCE_EFULL);
    }

    /* allocate used list(stack) */
    if( (  array_table[index].blank_pointer_stack =
           (entry_t **) VCEMALLOC( sizeof( entry_t *) * num ) )== NULL ) {
        VCE_ERROUT_V1( FATAL_ARRAY_FMALLOC2_D ,index);
        VCEFREE( array_table[index].master_buffer );
        VCEFREE( array_table[index].ent );
        return SET_LAST_ERROR(VCE_EFULL);
    }

    /* memset() is only here. Pointers will be kept when alloc/free from array. */
    memset( array_table[index].master_buffer , 0 , size * num );
    memset( array_table[index].ent , 0, sizeof( entry_t ) * num );
    memset( array_table[index].blank_pointer_stack , 0 , sizeof( entry_t * ) * num );


    /* Splitting master buffer */
    for( i = 0 ; i < num ; i++ ) {
        char *ptrdiv = array_table[index].master_buffer + size * i;
        array_table[index].ent[i].use = 0;
        array_table[index].ent[i].buf = ptrdiv;

        array_table[index].ent[i].next = NULL;
        array_table[index].ent[i].prev = NULL;

        /* put it in stack */
        array_table[index].blank_pointer_stack[i] = &array_table[index].ent[i];           
    }

    /* initialize entries */
    array_table[index].use = 1;
    array_table[index].num = num;
    array_table[index].size = size;
    array_table[index].blank_pointer_stack_pointer = 0;
    array_table[index].master_buffer_size = size * num;
    array_table[index].inuse_top_pointer = NULL;
    array_table[index].inuse_last_pointer = NULL;

    vce_copy_cstring( array_table[index].name, sizeof( array_table[index].name ), nm );
    VCE_ERROUT_V5( NOTE_INIT_ARRAY_OK_D_P_U_D_S, index,(void*) array_table[index].master_buffer, (unsigned int )size , num , nm );
	SET_LAST_ERROR(0);
    return index;
    
}

// deallocate array
int vce_end_array( int index ) {
    if( CHECKINDEX(index) || array_table[index].use == 0 ){
        return SET_LAST_ERROR(VCE_EINVAL);
    }

    VCEFREE( array_table[index].master_buffer );
    VCEFREE( array_table[index].ent );
    VCEFREE( array_table[index].blank_pointer_stack );
    array_table[index].use = 0;
    VCE_ERROUT_V1( "vce_end_array: index %d\n", index );
    return SET_LAST_ERROR(0);
}

void *vce_alloc_array_object( int index ) {
    int *sp;
    void *retp;
    entry_t *entp;

    if( CHECKINDEX(index) || array_table[index].use == 0 ){
		SET_LAST_ERROR(VCE_EINVAL );
        return NULL;
    }
    sp = &array_table[index].blank_pointer_stack_pointer;
    if( *sp == array_table[index].num ){
        VCE_ERROUT_V1( FATAL_ARRAY_FULL_S , array_table[index].name );
		SET_LAST_ERROR(VCE_EFULL );
        return NULL;
    }
    entp = array_table[index].blank_pointer_stack[*sp];
    (*sp)++;
    entp->use = 1;
    retp = entp->buf;

    /* update used list links. Always insert at the top */
    {
        entry_t *current_inuse_top;
        current_inuse_top = array_table[index].inuse_top_pointer;
        if( current_inuse_top ){
            current_inuse_top->prev = entp;
        } else {
            array_table[index].inuse_last_pointer = entp;
        }
        entp->next = current_inuse_top;
        entp->prev = NULL;
        array_table[index].inuse_top_pointer = entp;
    }
	 SET_LAST_ERROR(0);
	return retp;
}
    
int vce_free_array_object( int index , void *p ) {
    size_t d;
    int dindex , *sp;

    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        return SET_LAST_ERROR(VCE_EINVAL);
    }

    if( p == NULL ){
        VCE_ERROUT_V1(  WARN_FREE_NULL_S, array_table[index].name );
        return SET_LAST_ERROR(VCE_EINVAL);
    }

    if( (char*) p < (char*) array_table[index].master_buffer ){
        VCE_ERROUT_V3( WARN_FREE_OUTR_S_P_P , 
                       array_table[index].name , p ,
                       array_table[index].master_buffer );
        return SET_LAST_ERROR(VCE_EINVAL);
    }
    d = (char*) p - (char*)array_table[index].master_buffer;
    if( ( d % array_table[index].size ) != 0 ) {
        VCE_ERROUT_V4( WARN_FREE_ALIGN_S_P_P_U,
                       array_table[index].name ,
                       p ,
                       array_table[index].master_buffer,
                       (unsigned int)array_table[index].size );
        return SET_LAST_ERROR(VCE_EINVAL);
    }

    dindex =(int)( d / array_table[index].size);
    if( dindex >= array_table[index].num ){
        VCE_ERROUT_V4( WARN_FREE_OUTR2_S_P_P_U,
                       array_table[index].name ,
                       p ,
                       array_table[index].master_buffer,
                       (int)array_table[index].size * array_table[index].num );
        return SET_LAST_ERROR(VCE_EINVAL);
    }

    /* If stack pointer gets negative, it'd be a VCE bug.. */
    if( ( sp = &array_table[index].blank_pointer_stack_pointer ) == 0 ){
        VCE_ERROUT_V1( BUG_FREESTACK_OVERFLOW_S, array_table[index].name );
        return SET_LAST_ERROR(VCE_EBUG);
    }

    /* Can't free twice */
    if( array_table[index].ent[dindex].use == 0 ){
        VCE_ERROUT_V2( WARN_REFREE_S_P, array_table[index].name , p );
        return SET_LAST_ERROR(VCE_EBUG);
    }

    (*sp)--;
    array_table[index].blank_pointer_stack[*sp] =
        &array_table[index].ent[dindex];


    /* remove from used list */

    /* look at previous one */
    if( array_table[index].ent[dindex].prev ){
        array_table[index].ent[dindex].prev->next = array_table[index].ent[dindex].next;
    } else {
        array_table[index].inuse_top_pointer = array_table[index].ent[dindex].next;
    }

    /* look at latter one */
    if( array_table[index].ent[dindex].next ){
        array_table[index].ent[dindex].next->prev = array_table[index].ent[dindex].prev;
    } else {
        array_table[index].inuse_last_pointer = array_table[index].ent[dindex].prev;
    }

    array_table[index].ent[dindex].use = 0;

    return SET_LAST_ERROR(0);
}

void * vce_get_array_object_top( int index ) {
    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
		SET_LAST_ERROR( VCE_EINVAL );
		return NULL;
	}
					   
    if( array_table[index].inuse_top_pointer == NULL ){
		SET_LAST_ERROR( 0 );
		return NULL;
	}
	SET_LAST_ERROR(0);
    return array_table[index].inuse_top_pointer->buf;
}

void *vce_get_array_object_next( int index , void *p ) {
    size_t d;
    int dindex;

    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
		SET_LAST_ERROR(VCE_EINVAL );
		return NULL;
	}

    if( p == NULL ){
		SET_LAST_ERROR( VCE_EINVAL );
        return NULL;
    }

    d = (char*)p -(char*) array_table[index].master_buffer;
    if ( ( d % array_table[index].size ) != 0  ){
		SET_LAST_ERROR( VCE_EALIGNMENT );
        return NULL;
    }

    dindex =(int)( d / array_table[index].size);
    if( array_table[index].ent[dindex].next == NULL ){
		SET_LAST_ERROR(0);
		return NULL;
	}
	SET_LAST_ERROR(0);
    return array_table[index].ent[dindex].next->buf;
}
/* TODO: avoid full-scan */
void *vce_get_array_object_last( int index ) {
    if( CHECKINDEX(index) || array_table[index].use == 0 ){
        SET_LAST_ERROR(VCE_EINVAL);
        return NULL;
    } else {
        SET_LAST_ERROR(0);
        if( array_table[index].inuse_top_pointer ){
            return array_table[index].inuse_last_pointer->buf;
        } else {
            return NULL;
        }
    }
}
int vce_get_array_usenum( int index ) {
    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        SET_LAST_ERROR( VCE_EINVAL );
    }
	SET_LAST_ERROR(0);
    return array_table[index].blank_pointer_stack_pointer;
}

int vce_get_array_object_index( int index , const void *p ) {
    size_t d;
    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        return SET_LAST_ERROR( VCE_EINVAL );
    }
    d = (char*)p - (char*)array_table[index].master_buffer;
    if( ( d % array_table[index].size ) != 0 ){
        return SET_LAST_ERROR(VCE_EALIGNMENT);
    }
    return (int)( d / array_table[index].size );
}

int vce_if_included_in_array( int index, const void *p ) {
	size_t d;
	if( CHECKINDEX(index) || array_table[index].use == 0 ){
		return SET_LAST_ERROR(VCE_EINVAL);
	}
	d = (char*)p - (char*)array_table[index].master_buffer;
	if( ( d % array_table[index].size ) != 0 ){
		return 0;
	}
	if( d > array_table[index].master_buffer_size ){
		return 0;
	}
	return 1;
}

int vce_array_object_inuse( int index, void *p ) {
    int dindex,d;
    
    if( vce_if_included_in_array( index, p ) == 0 ) return 0;
	d = (int)((char*)p - (char*)array_table[index].master_buffer);
    if( d < 0 || d > (int)array_table[index].master_buffer_size ){
        return SET_LAST_ERROR(VCE_ERANGE);
    }
    dindex = d / (int)array_table[index].size;
    return array_table[index].ent[dindex].use;
}

void *vce_get_array_object_pointer_by_index( int index , int objindex ) {
    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        SET_LAST_ERROR(VCE_EINVAL );
        return NULL;
    }
    if( objindex < 0 || objindex >= array_table[index].num ){
        SET_LAST_ERROR( VCE_EINVAL );
        return NULL;
    }

    SET_LAST_ERROR(0);
    return ( void * ) array_table[index].ent[objindex].buf;
}
void *vce_get_array_object_pointer_by_index_only_used( int index, int objindex ) {
	if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        SET_LAST_ERROR( VCE_EINVAL );
        return NULL;
    }
	if( objindex < 0 || objindex >= array_table[index].num ){
        SET_LAST_ERROR( VCE_EINVAL );
        return NULL;
    }
	if( array_table[index].ent[objindex].use == 0 ){
        SET_LAST_ERROR(0);
        return NULL;
    }
    SET_LAST_ERROR(0);
	return (void*) array_table[index].ent[objindex].buf;
}

int vce_show_array_usage( int index , int show_all ) {
    entry_t *cur;
    int inuse = 0;
    if( CHECKINDEX( index ) || array_table[index].use == 0 ){
        return SET_LAST_ERROR(VCE_EINVAL);
    }
    cur = array_table[index].inuse_top_pointer;

    vce_errout( ":----------\n"
                ": index %d inuse_top_pointer:%p\n",
                index,
                array_table[index].inuse_top_pointer );
    while(1){
        if( cur == NULL ) break;
        if( cur->use ){
            size_t d = (char*)cur->buf -
                (char*)array_table[index].master_buffer;
            int dindex =(int)( d / array_table[index].size);
            if( show_all ){
                vce_errout( ": use:%d %p buf:%p(%d) prev:%p next:%p\n",
                            inuse , cur, cur->buf, dindex, cur->prev,
                            cur->next );
            }
            inuse++;
        } else {
            vce_errout( BUG_SHOW_ARRAY_USAGE_S_P,
                        array_table[index].name, cur );
            return SET_LAST_ERROR(VCE_EBUG);
        }
        cur = cur->next;
    }
    if( vce_get_array_usenum( index ) != inuse ){
        vce_errout( BUG_USENUM_NOMATCH_S_D_D,
                    array_table[index].name, vce_get_array_usenum(index), inuse );
        return VCE_EBUG;
    }

    vce_errout( ": inuse:%d usage-link is consistent: GOOD\n"
                ":---------\n" ,                inuse );

    SET_LAST_ERROR(0);
    return inuse;
}

void vce_end_all_array( void ) {
    int i;
    for( i = 0 ; i < vce_limit.max_array; i ++ ){
        if( array_table[i].use ){
            vce_end_array( i );
        }
    }
    SET_LAST_ERROR(0);
}

void vce_free_array_object_all( int index ) {
    void *cur;
    ARRAY_SCAN(index,cur){
        vce_free_array_object(index,cur);
    }
}

int vce_get_array_member_size( int index ) {
	if( CHECKINDEX(index) || array_table[index].use == 0 ){
		return SET_LAST_ERROR( VCE_EINVAL );
	}
	
	return (int)array_table[index].size;
}

int vce_get_array_maxnum( int index ) {
	if( CHECKINDEX(index) || array_table[index].use == 0 ){
		return SET_LAST_ERROR( VCE_EINVAL );
	}
    return array_table[index].num;
}
