workspace "RayTracingInOneWeekend"
	architecture "x64"
	configurations {"Debug", "Release"}
	
project "RayTracingInOneWeekend"
	kind "ConsoleApp"
	language "C++"
	targetdir "Build/%{cfg.buildcfg}"
	objdir ("Intermediate/%{cfg.buildcfg}")
	
	files {"**.h", "**.cpp"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
	