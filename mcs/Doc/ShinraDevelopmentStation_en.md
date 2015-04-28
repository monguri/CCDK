# Shinra Development Station
The Shinra Development Station (SDS) is in charge of managing Shinra game projects. Its main purpose is to create and modify project files.
Those project files can then be used to locally run games using MCS, or create
Shinra packages for Cloud deployment.

## Interface overview
The interface is composed of three main elements:
- **The menu bar** on the top gives access to most of the important actions like project loading and saving, or configuration settings of SDS itself.
- **The project tree** on the left gives a representation of the different elements of the project including the data packs and the startup configurations. Those two concepts are detailed in the "Shinra Project Structure" section below. You can select individual element in the tree to have access to its properties and edit them.
- **The contextual properties** on the right will display a set of properties you can edit. Those properties will vary depending on the selected item in the project tree.

## MCS configuration
You can check the MCS configuration by clicking "MCS Configuration" in the Settings menu.

**Python executable** is the path to python.exe used to execute the packaging script. Python 3 is required.

**Shinra script path** is the path to the shinra.py script used for packaging, game installation and execution. By default the path is deduced from a relative path from the SDS executable.

**Shinra MCS path** must be set to the directory where the MCS package was unzipped. This directory must contain the various executables and Dlls required to run a game in MCS environment. SDS will automatically create links and configuration files to run the game for you.

**Games installation dir** will be used as a root directory to deploy the game files locally and perform execution. Make sure it points to a directory where you have proper write access, and enough disk space to receive the files from the data packs.

**Default game user id** is the user id that will be used by default when creating new game instances.

When **Force overwriting of game data on install** is unchecked, and re-installing a game, only the data with a more recent changed date, or with a different file size will be overwritten. This enables to avoid unnecessary copy of big files when re-installing a game. You can disable this feature and force overwriting by checking this option.


## Shinra Project structure
A Shinra project is composed of two main parts: the **data packs** and the **startup configurations**.
A data pack allows to define a directory containing the data that will be included in the game deployment.
A startup configuration allows to define how a game has to be executed, and how MCS has to be configured for this execution.
The paths for executable and work directory are relative to the root of the a data pack, so your need to specify which data pack to use for each startup configuration.
The normal flow of configuration is to first create a data pack, and then to crate a startup configuration using an executable contained in this data pack.
The file hooks configuration is specific to MCS. You can check the "File hook" section in the MCS_REAMDE documentation for more details.

See "Shinra project file format" in MCS_README for more information on the shinra project file format.

### Create a data pack
You can create a new Data pack by three different means:
- Click "Add data pack" in the Project menu.
- Right click on the "Data packs" section in the project tree and select "Add data pack".
- Drag and drop a directory containing the data on the project tree.

Once you have your Data pack created, you can configure the different properties:
- **Id** is string used to identify this data pack from the others. It can be configured to your liking.
- **Version** is a string used only for tracking purpose.
- **Directory** is the path where the data you want to include is located.
- **Alias** is the name of the directory under which the data will be deployed. By default it is the same as the original directory name, but it can be changed for convenience.

### Create a startup configuration
You can create a new Startup configuration by three different means:
- Click "Add Startup configuration" in the Project menu.
- Right click on the "Startup configurations" section in the project tree and select "Add Startup configuration".
- For a given Data pack, right click on an executable file you want to start and select "Add startup configuration".

Once you have your Startup configuration created, you can configure the different properties:
- **Id** is a string used to identify this startup configuration form the others.
- **Executable** is the path to the executable inside the data pack.
- **Arguments** will be used when running the executable.
- **Work directory** will be used as the current work directory for the execution. The path is relative to Data pack itself.
- **Data pack** will be used as the reference for path definition.
- **Save data** is a list of Path filter expressions (or file hooks) used to define what game file needs to be redirected and saved on the end of a game execution. The data will be restored on the next execution of the same game for the same user.
- **Temp data** is a list of Path filter expressions (or file hooks) used to define what game file needs to be redirected and discarded on the end of a game execution.

See "File hooks" in MCS_README for more information on the file hooks configuration and inner workings.

Note you can drag the files from the data pack preview window to the text fields.
You can also have multiple startup configurations pointing at the same executable in the same data pack and using different arguments.

## MCS Game execution
Projects can be deployed locally and executed using MCS.

### Start a game
You can start a game using MCS in two different ways:
- In the Project menu select "Start game", then select the startup configuration you want to run.
- Right click on a given Startup configuration and select "Start game".

When starting a game, the game data will be deployed in the directory specified under the "MCS configuration", and then executed there. Once the installation is over you will be prompted the Game running window.

### Game running window
When running a game you are presented with a window enabling to start several instances of the game. Each instance is composed of:
- **User id** to be used for this particular instance of the game. Note we cannot have multiple instances of the same game with the same user id. Each instance has to have a specific user id.
- **Game port** to be used for this particular instance of the game. The port must be available and not conflict with the other ports of other game instances.
- **Video port** to be used for this particular instance of the game. The same restrictions than for the Game port applies here.
- **Game** start button. This will start the game instance itself with the specified user id, game port and video port.
- **Client** start button. This will start the client application with the specified game port and video port. By default the client is started automatically when the game is started. You can disable this option in case you want to run the client from another computer.

You can add a new game instance by right clicking in the list and select "Add game instance". You can remove a game instance by clicking on a instance and hit delete key.


## ShinraPack packaging
Projects can be packaged in a ShinraPack archive for deployment on the Cloud servers. 

### Create a ShinraPack
You can create a ShinraPack in two different ways:
- In the Project menu select "Build ShinraPack".
- Right click on the project item in the project tree and select "Start game".

## Importing a project
A package project can be re-imported to create a new shinra project. To import a project click File and Import project. This will open the import dialog box. You need to specify:
- Import from package: The zip file containing the packaged project.
- Store data in: A directory where the project data will be extracted to.
- Project file: The name of the new project file to be created.
