workspace "3DEngine"
	configurations { "Debug", "Release" }

project "3DEngine"
	location "3DEngine"
	language "C++"
	kind "ConsoleApp"

	targetdir ("3DEngine/bin")
	objdir ("3DEngine/obj")

	files 
	{ 
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/res",
		"%{prj.name}/src",
		"Dependencies/GLFW/include",
		"Dependencies/GLEW/include",
		"Dependencies/glm"
	}

	libdirs
	{
		"Dependencies/GLFW/lib-vc2022",
		"Dependencies/GLEW/lib/Release/x64"
	}

	links
	{
		"glfw3.lib",
		"glew32s.lib",
		"opengl32.lib"
	}

	defines
	{
		"GLEW_STATIC",
		"_MBCS"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		system "Windows"
		architecture "x64"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		system "Windows"
		architecture "x64"
		optimize "On"