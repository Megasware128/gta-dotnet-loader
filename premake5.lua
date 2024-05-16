projectName = "Megasware128.GTA.DotNetLoader"

workspace(projectName)
configurations { "Release", "Debug" }
location("project_files/")

project("Megasware128.GTA.Abstractions")
	kind "SharedLib"
	location("Megasware128.GTA.Abstractions/")

	language "C#"
	dotnetframework "net8.0"
	implicitusings "On"
	nullablereferences "On"

	enabledefaultcompileitems "true"

	filter "configurations:Debug"
		symbols "on"

	filter "configurations:Release"
		symbols "off"
		optimize "On"


project("Megasware128.GTA.Runtime")
	kind "SharedLib"
	location("Megasware128.GTA.Runtime/")

	language "C#"
	dotnetframework "net8.0"
	implicitusings "On"
	nullablereferences "On"

	enabledefaultcompileitems "true"

	nuget {
		"Microsoft.Extensions.Hosting:8.0.0",
		"Microsoft.VisualStudio.Composition:17.7.40",
		"NReco.Logging.File:1.2.0",
	}

	links { "Megasware128.GTA.Abstractions" }

	filter "configurations:Debug"
		symbols "on"

	filter "configurations:Release"
		symbols "off"
		optimize "On"


project(projectName)
kind "SharedLib"
location("project_files/")

language "C++"
clr "NetCore"
targetextension ".asi"
characterset ("MBCS")

links { "Megasware128.GTA.Runtime" }

targetdir("output/asi/")
objdir("output/obj/")

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"_CRT_NON_CONFORMING_SWPRINTFS",
	"_USE_MATH_DEFINES",
	"_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING"
}
cppdialect "C++17"
dotnetframework "net8.0"
enablemanagedpackagereferences "true"
copylockfileassemblies "true"

files {
	"source/*.cpp",
	"source/*.h",
}

includedirs {
	"$(PLUGIN_SDK_DIR)/shared/",
	"$(PLUGIN_SDK_DIR)/shared/game/",
}

libdirs {
	"$(PLUGIN_SDK_DIR)/output/lib/",
	"$(DXSDK_DIR)/Lib/x86/",
	"$(PLUGIN_SDK_DIR)/shared/bass/",
}

filter "configurations:Debug"
	defines { "DEBUG" }
	symbols "on"
	staticruntime "off"

filter "configurations:Release"
	defines { "NDEBUG" }
	symbols "off"
	optimize "On"
	staticruntime "off"

filter "configurations:*"
	targetname(projectName .. "SA")

	defines { "GTASA", "PLUGIN_SGV_10US", "RW" }

	includedirs {
		"$(PLUGIN_SDK_DIR)\\plugin_SA\\",
		"$(PLUGIN_SDK_DIR)\\plugin_SA\\game_SA\\",
	}

	debugdir "$(GTA_SA_DIR)"
	debugcommand "$(GTA_SA_DIR)/gta-sa.exe"
	debuggertype "NativeWithManagedCore"
	postbuildcommands("copy /y \"$(OutDir)\" \"$(GTA_SA_DIR)\\scripts\"")

	filter "configurations:Release"
		links { "plugin" }

	filter "configurations:Debug"
		links { "plugin_d" }
