workspace "Amarelo"
		architecture "x64"
		startproject "SandBox"


configurations
{
	"Debug",
	"Release",
	"Dist"
}

characterset ("MBCS")

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 IncludeDir = {}
  IncludeDir["glm"] = "Amarelo/vendor/glm"	

  group "Dependencies"
  include "Amarelo/vendor/glm"
  group ""

project "Amarelo"
	location "Amarelo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	toolset "v141"  

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glm}",
        "Amarelo/vendor",
	}


	filter "system:windows"
	systemversion "10.0.22621.0"

	defines
	{
		"AMARELO_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
	defines "AMARELO_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	defines "AMARELO_DEBUG"
	runtime "Release"
	optimize "Debug"

	filter "configurations:Dist"
	defines "AMARELO_DIST"
	runtime "Release"
	symbols "Off"
	optimize "Full"