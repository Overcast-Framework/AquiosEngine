# AquiosEngine



AquiosEngine is a general-purpose game engine made for 2D and (later 3D) desktop games.



\## Features



* OpenGL Rendering API (Vulkan in the works)
* Game loop (update / render architecture)
* Input handling system
* Platform and API-agnostic graphics backend
* Asset Manager
* Window System
* Layer Stack



Many more features are planned, however, due to the nature of the project, adding new features takes a long time.



\## How to compile it

Requirements:

* Visual Studio 2026
* Windows Machine (Linux not yet supported)
* premake5
* git



\# Step 1: Getting the code

The latest version of AquiosEngine can be found in the main branch. To properly clone the repository, use
`git clone --recurse-submodules https://github.com/Overcast-Framework/AquiosEngine.git`



\# Step 2: Generating project files

**MAKE SURE YOU'VE INSTALLED PREMAKE5 PRIOR TO THIS STEP!**



Generating project files is simple. Just run the generate\_vs2026.bat file or use `premake5 vs2026` in a terminal.

You can then open up the generated solution file in VS2026.



\# Step 3: Compiling the source code

Inside VS2026, just select the Sandbox project as your startup project and then hit `CTRL+B` to build it or `CTRL+F5` to run it.

That's all!



\## Status



This is an ongoing experimental project focused on learning about game engines and how they work.





