//
// Game.cpp -
//

#include "pch.h"
#include "Game.h"
#include "winsock2.h"
#include "ws2tcpip.h"
#include "vce.h"
#include "ssproto_cli.h"

using  Microsoft::WRL::ComPtr;

#define REALTIME_BACKEND_HOST "localhost"
#define REALTIME_BACKEND_PORT 22223

tcpcontext_t g_rtTcp;

int conn_closewatcher( conn_t c, CLOSE_REASON reason ) {
    bool fatal = false;
    OutputDebugString(L"closewatcher!" );    
    switch(reason) {
    case CLOSE_REASON_REMOTE:  // network error
    case CLOSE_REASON_TIMEOUT:
        fatal = true;
        break;
    case CLOSE_REASON_APPLICATION: // OK
        break;
    case CLOSE_REASON_UNKNOWN: // program error
    case CLOSE_REASON_DECODER:
    case CLOSE_REASON_ENCODER:
    case CLOSE_REASON_PARSER:
    case CLOSE_REASON_INTERNAL:
    default:
        fatal = true;
        break;        
    }

    if(fatal) {
		OutputDebugString(L"network fatal error");

	}
    return 0;
}
int ssproto_cli_sender( conn_t c, char *data, int len ) {
    //    print("ssproto_cli_sender: len:%d",len);
    int r = vce_protocol_unparser_bin32( c, data, len );
    if( r < 0 ) {
		if (vce_conn_is_valid(c))  OutputDebugString(L"ssproto_cli_sender: unparser_bin32 failed!");
    }
    return r;
}
int ssproto_cli_recv_error_callback( conn_t c, int e ) {
    OutputDebugString( L"ssproto_cli_recv_error_callback!" );
    return -1;
}


void globalInitNetwork() {
    static bool initialized = false;
    if(initialized==false) {
        vce_initialize();
        vce_set_verbose_mode(1);
        vce_set_heartbeat_wait_flag(0);
        g_rtTcp = vce_tcpcontext_create( 0, // client
                                         NULL, 0, // client socket doesn't need address
                                         1, // maxcon. need only 1 connection concurrent
                                         1024*1024, 1024*1024, // buffer size
                                         60, // timeout in seconds
                                         0,
                                         1, // nodelay
                                         0 );
        if( !g_rtTcp ) {
            OutputDebugString( L"can't initialize realtime Connection" );
        }
        vce_tcpcontext_set_conn_call_parser_per_heartbeat( g_rtTcp, 1000 );
        vce_tcpcontext_set_conn_parser( g_rtTcp, vce_protocol_parser_bin32, ssproto_cli_pcallback );
        vce_tcpcontext_set_conn_closewatcher( g_rtTcp, conn_closewatcher );
        
        initialized = true;
    }
}

// Constructor.
Game::Game() :
    m_window(0),
    m_featureLevel( D3D_FEATURE_LEVEL_11_1 ),
	m_framecnt(0),
    m_pong_recv_count(0),
    m_channel_joined(false),
    m_channelcast_notify_count(0)
{
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window)
{
    m_window = window;

	
    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
	m_spriteBatch = new SpriteBatch(m_d3dContext.Get());
	m_spriteFont = new SpriteFont( m_d3dDevice.Get(), L".\\assets\\tahoma32.spritefont");

	// This is only needed in Win32 desktop apps
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audioEngine = new AudioEngine(eflags);
	m_soundEffect = new SoundEffect(m_audioEngine, L".\\assets\\coinget.wav");
	m_soundEffect->Play();


	globalInitNetwork();

    m_rtConn = vce_tcpcontext_connect( g_rtTcp, REALTIME_BACKEND_HOST, REALTIME_BACKEND_PORT );

    if( !vce_conn_is_valid( m_rtConn)) {
        OutputDebugString( L"can't connect to backend");
    }
    OutputDebugString( L"connected to backend server" );
    
    ssproto_conn_serial_send( m_rtConn );
    ssproto_join_channel_send( m_rtConn, CHANNEL_ID );
}

// Executes basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here
    elapsedTime;

	m_audioEngine->Update();
	if (m_audioEngine->IsCriticalError()) {
		OutputDebugString(L"AudioEngine error!\n");
	}

    // networking
    if( vce_conn_is_valid( m_rtConn) ) {
        if( m_timer.GetFrameCount()%100 == 0 ) {
            OutputDebugString(L"sending ping\n");
            ssproto_ping_send( m_rtConn, (VCEI64) elapsedTime*1000, 0 );            
        }
        if( m_channel_joined ) {
            OutputDebugString(L"sending channelcast\n");
            char data[8] = { 0x10, 0x20, 0x30, 0x00, 0x12, 0x34, 0x56, 0x78 };               
            ssproto_channelcast_send( m_rtConn, CHANNEL_ID, PACKET_TYPE, data, sizeof(data) );
        }
    }
    vce_heartbeat();
}

// Draws the scene
void Game::Render()
{
	m_framecnt++;
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
        return;

    Clear();

    // TODO: Add your rendering code here
	m_spriteBatch->Begin();

	TCHAR statmsg[100];
	wsprintf(statmsg, L"Frame:%d  Ping:%d Channelcast:%d", m_framecnt, m_pong_recv_count, m_channelcast_notify_count );
	m_spriteFont->DrawString(m_spriteBatch, statmsg, XMFLOAT2(10, 10));

	m_spriteFont->DrawString(m_spriteBatch, L"Skeleton code for N:N games", XMFLOAT2(100, 100));
	m_spriteFont->DrawString(m_spriteBatch, L"Press P to play sound effect", XMFLOAT2(130, 160));
	m_spriteFont->DrawString(m_spriteBatch, L"Press Q to quit", XMFLOAT2(130, 200));

	m_spriteBatch->End();


    Present();
}

// Helper method to clear the backbuffers
void Game::Clear()
{
    // Clear the views
	float d = 100.0f;
	int m = 25;
	float r = (rand() % m) / d, g = (rand() % m) /d, b = (rand() % m) / d;
	float col[4] = { r,g,b,1 };
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), col );
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
}

// Presents the backbuffer contents to the screen
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized)
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize)
}

void Game::OnWindowSizeChanged()
{
    CreateResources();

    // TODO: Game window is being resized
}

// Properties
void Game::GetDefaultSize(size_t& width, size_t& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200)
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    // This flag adds support for surfaces with a different color channel ordering than the API default.
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling)
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify null to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,                                // leave as nullptr unless software device
        creationFlags,                          // optionally set debug and Direct2D compatibility flags
        featureLevels,                          // list of feature levels this app can support
        _countof(featureLevels),                // number of entries in above list
        D3D11_SDK_VERSION,                      // always set this to D3D11_SDK_VERSION
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if ( hr == E_INVALIDARG )
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
        hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                creationFlags, &featureLevels[1], _countof(featureLevels) - 1,
                                D3D11_SDK_VERSION, m_d3dDevice.ReleaseAndGetAddressOf(),
                                &m_featureLevel, m_d3dContext.ReleaseAndGetAddressOf() );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    hr = m_d3dDevice.As(&d3dDebug);
    if (SUCCEEDED(hr))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        hr = d3dDebug.As(&d3dInfoQueue);
        if (SUCCEEDED(hr))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed 
            };
            D3D11_INFO_QUEUE_FILTER filter;
            memset(&filter, 0, sizeof(filter));
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // TODO: Initialize device dependent objects here (independent of window size)
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    RECT rc;
    GetWindowRect( m_window, &rc );

    UINT backBufferWidth = std::max<UINT>( rc.right - rc.left, 1 );
    UINT backBufferHeight = std::max<UINT>( rc.bottom - rc.top, 1);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = (m_featureLevel >= D3D_FEATURE_LEVEL_10_0) ? DXGI_FORMAT_D32_FLOAT : DXGI_FORMAT_D16_UNORM;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(2, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), &dxgiFactory));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        HRESULT hr = dxgiFactory.As(&dxgiFactory2);
        if (SUCCEEDED(hr))
        {
            // DirectX 11.1 or later
            m_d3dDevice.As( &m_d3dDevice1 );
            m_d3dContext.As( &m_d3dContext1 );

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = 2;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a CoreWindow.
            DX::ThrowIfFailed( dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(), m_window, &swapChainDesc,
                &fsSwapChainDesc,
                nullptr, m_swapChain1.ReleaseAndGetAddressOf() ) );

            m_swapChain1.As( &m_swapChain );
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = 2;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed( dxgiFactory->CreateSwapChain( m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf() ) );
        }

        // This template does not support 'full-screen' mode and prevents the ALT+ENTER shortcut from working
        dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER);
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // Create a viewport descriptor of the full window size.
    CD3D11_VIEWPORT viewPort(0.0f, 0.0f, static_cast<float>(backBufferWidth), static_cast<float>(backBufferHeight));

    // Set the current viewport using the descriptor.
    m_d3dContext->RSSetViewports(1, &viewPort);

    // TODO: Initialize windows-size dependent objects here
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here

    m_depthStencil.Reset();
    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}
void Game::OnKeydown(int keycode) {
	TCHAR s[100];
	wsprintf(s, L"Key: %d", keycode);

	OutputDebugString(s);

	if (keycode == 'Q' ) exit(0); 
	if (keycode == 'P') m_soundEffect->Play();
}


// RPC receiver functions
int ssproto_conn_serial_result_recv(conn_t _c, int serial){
    TCHAR msg[100];
    wsprintf( msg, L"ssproto_conn_serial_result_recv: %d\n", serial );
    OutputDebugString( msg );
    return 0;
}
void receivePong();
int ssproto_pong_recv(conn_t _c, VCEI64 t_usec, int cmd) {
    receivePong();
    return 0;
}
void receiveJoinChannelOK();
int ssproto_join_channel_result_recv(conn_t _c, int channel_id, int retcode){
    assert( retcode == SSPROTO_OK );
    assert( channel_id == Game::CHANNEL_ID );
    receiveJoinChannelOK();
    return 0;
}
void receiveChannelcastNotify();
int ssproto_channelcast_notify_recv(conn_t _c, int channel_id, int sender_cli_id, int type_id, const char *data, int data_len){
    assert( type_id == Game::PACKET_TYPE );
    receiveChannelcastNotify();
    return 0;
}

int ssproto_broadcast_notify_recv(conn_t _c, int type_id, int sender_cli_id, const char *data, int data_len){return 0;}
int ssproto_version_notify_recv(conn_t _c, unsigned int maj, unsigned int min){ return 0; }

int ssproto_clean_all_result_recv(conn_t _c){ return 0; }
int ssproto_put_file_result_recv(conn_t _c, int query_id, int result, const char *filename) { return 0; }
int ssproto_get_file_result_recv(conn_t _c, int query_id, int result, const char *filename, const char *data, int data_len) { return 0; }
int ssproto_check_file_result_recv(conn_t _c, int query_id, int result, const char *filename){ return 0; }
int ssproto_ensure_image_result_recv(conn_t _c, int query_id, int result, int image_id){ return 0; }
int ssproto_update_image_part_result_recv(conn_t _c, int query_id, int result, int image_id){ return 0; }
int ssproto_get_image_png_result_recv(conn_t _c, int query_id, int result, int image_id, const char *png_data, int png_data_len){ return 0; }
int ssproto_get_image_raw_result_recv(conn_t _c, int query_id, int result, int image_id, int x0, int y0, int w, int h, const char *raw_data, int raw_data_len){ return 0; }
int ssproto_generate_id_32_result_recv(conn_t _c, int query_id, int generated_id_start, int num){ return 0; }
int ssproto_kvs_command_str_result_recv(conn_t _c, int query_id, int retcode, int valtype, const char * const *result, int result_len){ return 0; }
int ssproto_kvs_push_to_list_result_recv(conn_t _c, int query_id, int retcode, const char *key, int updated_num){ return 0; }
int ssproto_kvs_get_list_range_result_recv(conn_t _c, int query_id, int retcode, int start_ind, int end_ind, const char *key, const char * const *result, int result_len){ return 0; }
int ssproto_kvs_append_string_array_result_recv(conn_t _c, int query_id, int retcode, const char *key, const char *field){ return 0; }
int ssproto_kvs_get_string_array_result_recv(conn_t _c, int query_id, int retcode, const char *key, const char *field, const char * const *result, int result_len){ return 0; }
int ssproto_kvs_save_bin_result_recv(conn_t _c, int query_id, int retcode, int valtype, const char *key, const char *field){ return 0; }
int ssproto_kvs_load_bin_result_recv(conn_t _c, int query_id, int retcode, int has_data, const char *key, const char *field, const char *data, int data_len){ return 0; }
int ssproto_counter_get_result_recv(conn_t _c, int counter_category, int counter_id, int result, int curvalue){ return 0; }
int ssproto_share_project_result_recv(conn_t _c, int project_id){ return 0; }
int ssproto_publish_project_result_recv(conn_t _c, int project_id){ return 0; }
int ssproto_search_shared_projects_result_recv(conn_t _c, int user_id, const int *project_ids, int project_ids_len){ return 0; }
int ssproto_search_published_projects_result_recv(conn_t _c, const int *project_ids, int project_ids_len){ return 0; }
int ssproto_project_is_joinable_result_recv(conn_t _c, int project_id, int user_id, int result){ return 0; }
int ssproto_is_published_project_result_recv(conn_t _c, int project_id, int published){ return 0; }
int ssproto_is_shared_project_result_recv(conn_t _c, int project_id, int shared){ return 0; }
int ssproto_list_presence_result_recv(conn_t _c, int project_id, const int *user_ids, int user_ids_len){ return 0; }
int ssproto_count_presence_result_recv(conn_t _c, int project_id, int user_num){ return 0; }
int ssproto_lock_grid_result_recv(conn_t _c, int grid_id, int x, int y, int retcode){ return 0; }
int ssproto_unlock_grid_result_recv(conn_t _c, int grid_id, int x, int y, int retcode){ return 0; }
int ssproto_lock_project_result_recv(conn_t _c, int project_id, int category, int retcode){ return 0; }
int ssproto_unlock_project_result_recv(conn_t _c, int project_id, int category, int retcode){ return 0; }


int ssproto_leave_channel_result_recv(conn_t _c, int retcode){ return 0; }
int ssproto_nearcast_notify_recv(conn_t _c, int channel_id, int sender_cli_id, int x, int y, int range, int type_id, const char *data, int data_len){ return 0; }
int ssproto_get_channel_member_count_result_recv(conn_t _c, int channel_id, int maxnum, int curnum){ return 0; }

