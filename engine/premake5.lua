project "AquiosEngine"
   kind "StaticLib"
   language "C++"
   files { "src/**.cpp", "src/**.h", "../vendors/glad/src/glad.c" }
   defines { "GLFW_INCLUDE_NONE" }
   targetdir "bin/%{cfg.buildcfg}"

   libdirs {
    ""
   }
   links { "glfw3", "spdlog", "opengl32" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
