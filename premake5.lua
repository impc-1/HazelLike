workspace "HazelLike"
	configurations {"Debug","Release","Dist"}
	architecture "x64"
	staticruntime "Off"
	startproject "Sandbox"
	 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includeDir = {}
includeDir["GLFW"] = "HazelLike/vendor/GLFW/include"
includeDir["Glad"] = "HazelLike/vendor/Glad/include"
includeDir["ImGui"] = "HazelLike/vendor/imgui"
--includeDir["glm"] = "HazelLike/vendor/glm"
-- include add glfw -> lua, glad-> lua
include "HazelLike/vendor/GLFW"
include "HazelLike/vendor/Glad"
include "HazelLike/vendor/imgui"
	
project "HazelLike"
	location "HazelLike"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "HazelLike/src/hzpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		--"%{prj.name}/vendor/glm/**.hpp",
	}

	includedirs 
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}"
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		
		systemversion "10.0.17763.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		-- 这里写了构建完成dll后执行复制语句
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .."/Sandbox/\"")
		}
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"HazelLike/vendor/spdlog/include",
		"HazelLike/vendor/glm",
		"HazelLike/src"
	}
	links
	{
		"HazelLike"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.17763.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"
