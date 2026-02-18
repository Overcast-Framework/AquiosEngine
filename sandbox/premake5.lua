project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"

   targetdir ("../bin/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")
   objdir ("../bin-int/" .. "%{cfg.buildcfg}" .. "/%{prj.name}")
   debugdir "$(SolutionDir)"

   files {
    "src/**.cpp",
    "src/**.h"
   }

   includedirs {
    "src",
    "../engine/src",

    "../vendors/glad/include",
    "../vendors/glfw/include",
    "../vendors/glm",
    "../vendors/spdlog/include",
    "../vendors/imgui"
   }

   filter "action:vs*"
        buildoptions { "/utf-8" }

   libdirs {
    "bin/" .. "%{cfg.buildcfg}" .. "/AquiosEngine"
   }

   links { "AquiosEngine" }

   filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

   filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"