workspace "Empaerior"
	architecture "x64"
	 
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
	staticruntime "On"
	systemversion "10.0.18362.0"	
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	
	
	includedirs
	{
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2/include",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_image/include",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_mixer/include",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_ttf/include"
	}
	libdirs 
	{ 
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2/lib/x64",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_image/lib/x64",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_mixer/lib/x64",
	"C:/Users/Dan/Desktop/Empaerior-Engine/SDL2_ttf/lib/x64"
	}
	links 
	{ 
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"SDL2_mixer.lib"
	}
	
	configuration "Debug"
         runtime "Debug"
		 symbols "on"

    configuration "Release"
         runtime "Debug"
         optimize "on"
		 
	configuration "Dist"
		runtime "Release"
		symbols "on"
	