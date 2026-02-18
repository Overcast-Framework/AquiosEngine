project "AquiosEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   pchheader "aqpch.h"
   pchsource "src/aqpch.cpp"

   multiprocessorcompile ("On")

   targetdir ("../bin/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")
   objdir ("../bin-int/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")

   files { 
    -- Engine Project Files
    "src/**.cpp", 
    "src/**.h", 

    -- GLAD
    "../vendors/glad/src/glad.c"
   }

   filter "files:**.c"
      enablepch "Off"
   filter {}

   defines { "GLFW_INCLUDE_NONE" }

   includedirs {
    "src",
    "../vendors/glad/include",
    "../vendors/glfw/include",
    "../vendors/glm",
    "../vendors/imgui",
    "../vendors/spdlog/include"
   }

   libdirs {
    "../bin/" .. "%{cfg.buildcfg}" .. "glfw",
    "../bin/" .. "%{cfg.buildcfg}" .. "imgui",
    "../bin/" .. "%{cfg.buildcfg}" .. "spdlog",
   }

   links { "glfw", "imgui", "opengl32", "spdlog" }

   filter "action:vs*"
      buildoptions { "/utf-8" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
