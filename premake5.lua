workspace "Empaerior"
	architecture "x86"
	 
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{}"

project "Empaerior"
	location "Empaerior"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	

	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"
	
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	
	includedirs
	{
	"%{prj.name}/src",
	"SDL2/include",
	"SDL2_image/include",
	"SDL2_mixer/include",
	"SDL2_ttf/include"
	}
	libdirs 
	{ 
	"SDL2/lib/x86",
	"SDL2_image/lib/x86",
	"SDL2_mixer/lib/x86",
	"SDL2_ttf/lib/x86"
	}
	links 
	{ 
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"SDL2_mixer.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
	
	
	configuration "Debug"
         runtime "Debug"
		 symbols "on"

    configuration "Release"
         runtime "Debug"
         optimize "on"
		 
	configuration "Dist"
		runtime "Release"
		symbols "on"
	