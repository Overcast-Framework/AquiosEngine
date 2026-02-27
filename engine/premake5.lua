project "AquiosEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   pchheader "aqpch.h"
   pchsource "src/aqpch.cpp"

   multiprocessorcompile ("On")

   targetdir ("../bin/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")
   objdir ("../bin-int/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")

   local vulkan_sdk = os.getenv("VULKAN_SDK")
   if not vulkan_sdk then
       error("VULKAN_SDK environment variable not set. Please install Vulkan SDK.")
   end

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
    "../vendors/spdlog/include",
    "../vendors/vk-bootstrap/src",
    "../vendors/vma/include",
    os.getenv("VULKAN_SDK") .. "/Include",  
   }

   libdirs {
    "../bin/" .. "%{cfg.buildcfg}" .. "glfw",
    "../bin/" .. "%{cfg.buildcfg}" .. "imgui",
    "../bin/" .. "%{cfg.buildcfg}" .. "spdlog",
    "../bin/" .. "%{cfg.buildcfg}" .. "vk-bootstrap",
    os.getenv("VULKAN_SDK") .. "/Lib"
   }

   links { "glfw", "imgui", "opengl32", "spdlog", "vulkan-1", "vk-bootstrap" }

   filter "action:vs*"
      buildoptions { "/utf-8" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
