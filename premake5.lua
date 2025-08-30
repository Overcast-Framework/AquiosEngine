workspace "AquiosEngine"
   configurations { "Debug", "Release" }
   architecture "x86_64"
   
   include "vendors/spdlog/premake5.lua"
   include "vendors/glfw/premake5.lua"
   include "vendors/imgui/premake5.lua"
   include "engine/premake5.lua"
   include "sandbox/premake5.lua"