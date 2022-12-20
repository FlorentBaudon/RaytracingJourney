workspace "RayTracingInOneWeekend"
	architecture "x64"
	configurations {"Debug", "Release"}
	
project "RayTracingInOneWeekend"
	kind "ConsoleApp"
	language "C++"
	targetdir "Build/%{cfg.buildcfg}"
	objdir ("Intermediate/%{cfg.buildcfg}")
	
	files {"**.h", "**.cpp"}
	
   includedirs
   {
      "src",
      "./vendor/raylib-4.2.0_win64_msvc16/include",
   }
	
	
	libdirs { 
		"./vendor/raylib-4.2.0_win64_msvc16/lib",
	}
	
	links { 
		"winmm.lib",
		"raylib.lib"
	}
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
	