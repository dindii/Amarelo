project "glm"
    kind "StaticLib"
    language "C"
	staticruntime "on"
    toolset "v141"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"glm",
		"glm/gtc",
		"glm/gtx",
		"glm/ext",
		"glm/simd",
		"glm/detail"
	}
    
    filter "system:windows"
        systemversion "10.0.22621.0"

      defines
	  {
		"_CRT_SECURE_NO_WARNINGS",
	 	"AMARELO_PLATFORM_WINDOWS"
	  }

     filter "configurations:Debug"
	 	defines "AMARELO_DEBUG"
        runtime "Debug"
        symbols "on"             -- Deixamos on os debug symbols
        
     filter "configurations:Release"
	 	defines "AMARELO_DEBUG"
        runtime "Release"
        optimize "on"            -- Ripamos todas as configurações de debug e otimizamos o projeto


     filter "configurations:Dist"
	 defines "AMARELO_DIST"
	 runtime "Release"
	 symbols "Off"
	 optimize "Full"