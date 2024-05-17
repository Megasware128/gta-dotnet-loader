projectName = "Megasware128.GTA.DotNetLoader"

workspace(projectName)
configurations { "ReleaseSA", "DebugSA", "ReleaseVC", "DebugVC", "ReleaseIII", "DebugIII" }
location("project_files/")

project("Megasware128.GTA.Abstractions")
	kind "SharedLib"
	location("Megasware128.GTA.Abstractions/")

    configmap {
        ["ReleaseSA"] = "Release",
        ["DebugSA"] = "Debug",
        ["ReleaseVC"] = "Release",
        ["DebugVC"] = "Debug",
		["ReleaseIII"] = "Release",
		["DebugIII"] = "Debug",
    }

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

    configmap {
        ["ReleaseSA"] = "Release",
        ["DebugSA"] = "Debug",
        ["ReleaseVC"] = "Release",
        ["DebugVC"] = "Debug",
		["ReleaseIII"] = "Release",
		["DebugIII"] = "Debug",
    }

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

objdir("output/obj/")

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"_CRT_NON_CONFORMING_SWPRINTFS",
	"_USE_MATH_DEFINES",
	"_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING"
}
cppdialect "C++20"
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
	"vcpkg_installed/x86-windows/include/",
}

libdirs {
	"$(PLUGIN_SDK_DIR)/output/lib/",
	"$(DXSDK_DIR)/Lib/x86/",
	"$(PLUGIN_SDK_DIR)/shared/bass/",
}

filter "configurations:Debug*"
	defines { "DEBUG" }
	symbols "on"
	staticruntime "off"

    debuggertype "NativeWithManagedCore"

filter "configurations:Release*"
	defines { "NDEBUG" }
	symbols "off"
	optimize "On"
	staticruntime "off"

filter "configurations:*SA"
	targetname(projectName .. "SA")
    targetdir("output/asi/SA/")    

	defines { "GTASA", "PLUGIN_SGV_10US", "RW" }

	includedirs {
		"$(PLUGIN_SDK_DIR)\\plugin_SA\\",
		"$(PLUGIN_SDK_DIR)\\plugin_SA\\game_SA\\",
	}

	debugdir "$(GTA_SA_DIR)"
	debugcommand "$(GTA_SA_DIR)/gta-sa.exe"
	postbuildcommands("copy /y \"$(OutDir)\" \"$(GTA_SA_DIR)\\scripts\"")

	filter "configurations:ReleaseSA"
		links { "plugin" }

	filter "configurations:DebugSA"
		links { "plugin_d" }

filter "configurations:*VC"
    targetname(projectName .. "VC")
    targetdir("output/asi/VC/")

	characterset ("Unicode")

    defines { "GTAVC", "PLUGIN_SGV_10EN", "RW" }

    includedirs {
        "$(PLUGIN_SDK_DIR)\\plugin_VC\\",
        "$(PLUGIN_SDK_DIR)\\plugin_VC\\game_VC\\",
    }

    debugdir "$(GTA_VC_DIR)"
    debugcommand "$(GTA_VC_DIR)/gta-vc.exe"
    postbuildcommands("copy /y \"$(OutDir)\" \"$(GTA_VC_DIR)\\scripts\"")

    filter "configurations:ReleaseVC"
        links { "plugin_vc" }

    filter "configurations:DebugVC"
        links { "plugin_vc_d" }

filter "configurations:*III"

	targetname(projectName .. "III")
	targetdir("output/asi/III/")

	characterset ("Unicode")

	defines { "GTA3", "PLUGIN_SGV_10EN", "RW" }

	includedirs {
		"$(PLUGIN_SDK_DIR)\\plugin_III\\",
		"$(PLUGIN_SDK_DIR)\\plugin_III\\game_III\\",
	}

	debugdir "$(GTA_III_DIR)"
	debugcommand "$(GTA_III_DIR)/gta3.exe"
	postbuildcommands("copy /y \"$(OutDir)\" \"$(GTA_III_DIR)\\scripts\"")

	filter "configurations:ReleaseIII"
		links { "plugin_iii" }

	filter "configurations:DebugIII"
		links { "plugin_iii_d" }
