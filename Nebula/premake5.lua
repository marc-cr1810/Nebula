project "Nebula"
	kind "ConsoleApp"
	language "C"
	cppdialect "C++17"
  cdialect "C17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c"
	}

	includedirs
	{
		"src"
	}

	links
	{
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PC_RELEASE"
		runtime "Release"
		optimize "on"

