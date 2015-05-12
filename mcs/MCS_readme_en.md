# Shinra MCS
Shinra MCS is a minimal emulator of Shinra Remote Renderer.

## <a name="InstallHowTo"></a> How to install
1. Install Python 3.4 if not already present on your computer.
2. Unpack the ShinraMCS.zip file on a local drive.
3. Check configuration in the ShinraMCS/python/shinra.py script. The two variables STORE_PATH and ARCHIVE_PATH contains path to directories where games data will be saved. Make sure they point to places where you have enough disk space and proper access rights (see ["File hooks"](#FileHooks) section for more information on these configurations).
5. Run ShinraDevelopmentStation.exe, and check the configuration in Settings->MCS Configuration. Make sure the path to the python 3.4 executable is correct. The path to the shinra.py script and the MCS directory should be ok. The "Games installation dir" will be used to install games data for running games, make sure this points to a place where you have enough disk space and proper access rights.

## <a name="SDS"></a> Shinra Development Station
The Shinra Development Station (or SDS) is a graphical interface used to create and manage projects. It is mainly a graphical layer on top of the shinra.py script and the MCS libraries.
For more information in SDS you can check the ShinraDevelopmentStation documentation.

## <a name="ShinraScript"></a> Shinra python script
In the python directory of MCS, you can find the shinra.py script. The shinra.py script is used to handle packaging, game installation and execution. It can be used as a stand-alone tool to automate ShinraPack generation, game execution and some deployment tasks.

```
usage: shinra.py [-h] [--mcs-install MCS_INSTALL]
                 [--log-level {DEBUG,INFO,WARN,ERROR}] [--log-file LOG_FILE]
                 {package,install,project,run} ...

Shinra MCS management script.

positional arguments:
  {package,install,project,run}
                        command help.
    package             Create a Shinra package from a project.
    install             Install a game from a project.
    project             Build a project from a package.
    run                 Run an installed game.

optional arguments:
  -h, --help            show this help message and exit
  --mcs-install MCS_INSTALL
                        Directory where MCS is installed. By default it is
                        assumed shinra.py is placed in the python directory
                        under the MCS installation path.
  --log-level {DEBUG,INFO,WARN,ERROR}
  --log-file LOG_FILE
```

### Package command
```
usage: shinra.py package [-h] project archive

positional arguments:
  project     Shinra project to use.
  archive     Shinra package to create.

optional arguments:
  -h, --help  show this help message and exit
```

The following example produces the package "package.zip" from the project file "project.shinra":
```
shinra.py package project.shinra package.zip
```

### Install command
```
usage: shinra.py install [-h] [-overwrite]
                         project startup dir

positional arguments:
  project         Shinra project to install.
  startup         Id of the startup configuration to install.
  dir             Installation directory.

optional arguments:
  -h, --help      show this help message and exit
  -overwrite      Force overwrite of files on install. By default, only files
                  with a older modification date than the source are
                  overwritten on install.
```

The following example installs the SSW startup configuration from the project "project.shinra" in the "C:\Flare\Games\SSW" directory:
```
shinra.py install project.shinra SSW C:\Flare\Games\SSW
```

### <a name="RunCommand"></a> Run command
```
usage: shinra.py run [-h] dir userid gameid gameport videoport

positional arguments:
  dir         Path to the game installation.
  userid      User id to use to run the game.
  gameid      Startup id to use to run the game.
  gameport    Port to use for game communications.
  videoport   Port to use for video communications.

optional arguments:
  -h, --help  show this help message and exit
```
The following example starts a game instance for the SSW startup configuration, using the user "user47", game port 60001 and video port 60000.
```
shinra.py run C:\Flare\Games\SSW user47 SSW 60001 60000
```
Note the client has to be executed with a matching port configuration to be able to connect ([see "Shinra Client" for more information](#ShinraClient)).

### Project command

```
usage: shinra.py project [-h] archive dir project

positional arguments:
  archive     Shinra package to use as source.
  dir         Directory where to store project data.
  project     Name of Shinra project file to create.

optional arguments:
  -h, --help  show this help message and exit
```

The following example will extract the package data in "C:\Path\to\data", and create a new project file with the proper datapack configuration pointing to the extracted data, and the corresponding startup configurations.
```
shinra.py project archive.zip C:\Path\to\data project.shinra
```

## <a name="ShinraClient"></a> Shinra Client
ShinraClient.exe can be found in the MCS installation directory under <MCS_INSTALL>/Shinra/x32/Release/ShinraClient.exe.
It is the client application in charge of interacting with the player. It displays the game video, plays the game audio and
sends the player inputs to the game server.
You can manually run the ShinraClient to connect to a game instance running on a distant computer. When connecting to an existing game instance, make sure you specify the proper server IP, game port and video port.


Parameters:
- -t : Server IP or host-name of the game server.
- -pv : Video Port
- -pg : Game Port

Following is an example connecting to a game instance running on the local computer, using game port 60001 and video port 60000.
```
<MCS_INSTALL>/Shinra/x32/Release/ShinraClient.exe -t 127.0.0.1 -pg 60001 -pv 60000
```

## <a name="ShinraProject"></a> Shinra project file format
Shinra projects are json text files containing the necessary information for:
- packaging and deployment of game data (dataPacks),
- execution and configuration of the game (startups).

The SDS interface is the preferred way to create and edit project files. But the project structure is simple enough so you can manually edit it. The following is an example of a simple configuration with one datapack, and one startup configuration.

```
{
    "dataPacks": [
        {
            "files": [
                {
                    "aliasPath": "",
                    "fileSystemPath": "D:\\Shinra\\import\\DX3\\DX3"
                }
            ],
            "id": "DX3",
            "version": "1"
        }
    ],
    "projectName": "DX3",
    "projectVersion": "1",
    "startups": [
        {
            "FileHooks": {
                "CloudFilteredPaths": [
                    "<RoamingAppData>\\Eidos Montreal\\**"
                ],
                "TempFilteredPaths": [
                    "<LocalAppData>\\dxhr\\**"
                ]
            },
            "arguments": "-archive",
            "dataPackId": "DX3",
            "executable": "DX3.exe",
            "id": "DX3",
            "workDir": ""
            "CustomProperties": {}
        }
    ]
}
```

- **projectName**: Name of the project
- **projectVersion**: Version number only used for tracking purposes.
- **dataPacks[].id**: Id of the data pack. This Id is used to reference the datapack across the project and must be unique for each datapack. 
- **dataPacks[].version**: Version of the datapack, Only used for tacking purposes.
- **dataPacks[].files[].fileSystemPath**: Path to a directory containing the files to be deployed for the game.
- **dataPacks[].files[].aliasPath**: path to append to the existing path on installation.
- **startups[].id** : Id of the startup configuration. This id is used to reference this configuration across the project. It will be used to create a GameID for game execution.
- **startups[].dataPackId** : Id of the datapack containing the files required by this startup configuration.
- **startups[].executable** : Path to the executable file used to run the game. This path is relative to the datapack root.
- **startups[].arguments** : Line command arguments to be passed to the executable. See ["Startup arguments"](#StartupArgs) for more informations.
- **startups[].workDir** : Path of the work directory to be used to run the executable. This path is relative to the datapack root.
- **startups[].FileHooks.CloudFilteredPaths** : List of file hook filters used for cloud storage data. See ["File hooks"](#FileHooks) for more information.
- **startups[].FileHooks.TempFilteredPaths** : List of file hook filters used for temporary game data. See ["File hooks"](#FileHooks) for more information.
- **startups[].CustomProperties** : List of custom values to used for properties. See  ["Custom properties"](#CustomProperties) for more information.

## <a name="StartupArgs"></a> Startup arguments
The arguments field of a startup configuration can contain some special variable that will be automatically replaced when running the game instance:
- {UserId} : will be replaced by the id of the user running the game instance.

Following is a simple example of command line including {UserId}. 
```
--debug --username={UserId} --dbhost=10.137.16.50 --rthost=10.137.16.50
```
When a new game instance is executed using shinra.py script ([see "Run command"](#RunCommand)), the id of the user is replaced in place just before executing the game instance for this user.
```
--debug --username=user47 --dbhost=10.137.16.50 --rthost=10.137.16.50
```

## <a name="CustomProperties"></a> Custom properties
The CustomProperties field of a startup configuration is used to force some settings in the CloudProperties.json configuration file. You can find more about the format and the content of the CloudProperties file in the ["CloudProperties"](#CloudProperties) section. 

The following example will overwrite the property Cloud.Debug.BreakOnStartup to True, and Cloud.Local.EndoferThreads to 3. Note the property names are case sensitive.
```
"CustomProperties": {
  "Debug.BreakOnStartup": True,
  "Local.EncoderThreads": 3,
}
```

## <a name="FileHooks"></a> File hooks
Shinra projects enable to define File Hooks for games. These File hooks are used to redirect the file-system access of the game application to a different place. This redirection is completely transparent to the game application. The main goal of these file access redirection is to enable running two instances of the same game with the same Windows user on the same machine, and avoid file conflicts when those different instances try to access the user's data.
The file hook redirection depends on the Shinra UserID and the GameID to make sure each instance is isolated from the other.

There are two kinds of file hook redirection:
- Temp hooks: files redirected by these hooks will be discarded when the game is over. These hooks are only to work-around multiple instances accessing the same data.
- Cloud save hooks: files redirected by these hooks will be saved when the game is over, and restored at the next game execution for the same user. See "Cloud save files" section for more information.

If a particular file path is matched by both Temp and Cloud file hooks, the Temp hooks have priority so the file won't be saved.

### File hook syntax
A File hook is defined by a pattern used to match the path of the files accessed by the application. To define a pattern, you have access to some predefined variables and wildcard operators.

Predefined variables:
- \<USERID\> : The Shinra UserID as specified when starting the game instance.
- \<EXEPATH\> : Path where the game executable is running.
- \<USERNAME\> : Windows user name.
- \<Profile\> : Windows profile folder for the current user.
- \<Documents\> : Windows Document folder for the current user.
- \<LocalAppData\> : Windows AppData/Local folder for the current user.
- \<LocalAppDataLow\> : Windows AppData/LocalLow folder for the current user.
- \<RoamingAppData\> : Windows AppData/Roaming folder for the current user.

Wildcard operators:
- some/path/* : Simple star \* matches all the files directly under some/path, but none of the sub-directories.
- some/path/** : Double star \** matches all the files under some/path, and all its sub-directories.

The following example will match all the files under "C:\Users\user47\AppData\Roaming\Eidos Montreal\":
```
<RoamingAppData>\Eidos Montreal\**
```

### File hook redirection
When the application tries to access a file that matches a file hook, this file access will be redirected to a different path. This new path will depend on:
- STORE_PATH variable defined in the shinra.py script
- UserID used to start the game instance
- GameID used to start the game instance
- Type of the hook (Temp or Cloud)

The file will be redirected to:
```
<STORE_PATH>/UserFiles/<UserID>/<GameID>/<Type>/
```

### Cloud save files
Between to executions of a game instance, the user's data for a particular game is stored in a tar.gz archive. This archive is stored in a directory depending on:
- ARCHIVE_PATH variable defined in the shinra.py script
- UserID used to start the game instance
- GameID used to start the game instance

The save data for a particular user will be:
```
<ARCHIVE_PATH>/<UserID>/<GameID>.tar.gz
```


## How to play remotely

Just unpack the library in the remote computer, then edit the StartShinraClient.bat to point to the IP address where you run the game, and set the game port and video port to match those defined for the corresponding game instance you want to connect to. You can then start the Shinra Client and connect to your game. See ["Shinra client"](#ShinraClient) for more information on the command line parameters for ShinraClient.exe.

## <a name="CloudProperties"></a>CloudProperties options

MCS games are reading their configuration from a CloudProperties.json file. When running a game with the shinra.py script, a CloudProperties file is automatically created for the new instance.

You can make your own CloudProperties.json files using the sample file under <MCS_INSTALL>/CloudProperties.json. The file has to be placed next to the game executable.

The CloudProperties.json contains a default configuration to allow the game to run smoothly in Shinra MCS configuration.  Some options inside it can be change to provide a better experience. The properties are presented with the following syntax:

    Cloud.Section.Name: default

which correspond to the following [JSON](http://json.org) property:

    { "Cloud": { "Section": { "Name": default } } }

* Cloud.Performance.MaxFPS: 30

  The maximum number of frames requests per second, after which the game start to be throttled down by pausing in the render thread.

* Cloud.Session.TokenTimeoutSec: 120

  The maximum number of seconds before the game stop accepting new connections.

* Cloud.Local.EncoderThreads: 1

  The number of threads dedicated to encoding the video stream.

* Cloud.Local.MaxRenderingFrames: 3

  The maximum number of queued rendering frame requested before the game start to block.

* Cloud.Local.MaxEncodingFrames: 5

  The maximum number of queued encoding frame requested before the game start to block. 


## FAQ

1. <a name="FAQ1"></a>Is MCS the same as Shinra Remote Rendering technology ?

   Shinra MCS used the same abstraction of the Direct X API to generate the rendering commands on Shinra Remote Renderer.  The implementation is however independent and simplified, and does not include many hardware acceleration and optimizations allowing Shinra Remote Renderer to scale to many clients on a single server.  It's also used a simple JPEG encoder instead of Shinra optimized encoder.

2. <a name="FAQ2"></a>My game is slower when I used Shinra MCS... will it be also the case with the Shinra Remote Renderer ?
   
   As said in [question 1](#FAQ1), Shinra MCS is an independant implementation of the Shinra Remote Renderer technology. It uses no hardware acceleration, can't share any resources from other clients and uses a software-only encoder delivering a bigger video stream.  It's also use the same resources as the client itself (it run in the same process) which can slow down your game further.  Briefly, Shinra MCS just try to imitate the Remote Rendering experience but aren't intend as a benchmark for the kind of performance you can get from Shinra Remote Rendering.
   
3. <a name="FAQ3"></a>Which port is used by MCS ?

   Shinra MCS used the following ports by default (with the <a href="#CloudProperties">CloudProperties</a> name in parenthesis) :
   
   * Video Port (`Cloud.Network.VideoPort`): 60000
   * Audio/Game Port (`Cloud.Network.GamePort`): 60001
   
   You can change which ports the ShinraMCS `-pv` and `-pg` (respectively for video and game port) options like this:
   
       ShinraClient -t localhost -pv 70000 -pg 70001

## Contacts

For more information, you can contact [fabien.ninoles@eidosmontreal.com](mailto:fabien.ninoles@eidosmontreal.com).

   