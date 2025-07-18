# GTA .NET Loader

[![Build](https://github.com/Megasware128/gta-dotnet-loader/actions/workflows/build.yml/badge.svg)](https://github.com/Megasware128/gta-dotnet-loader/actions/workflows/build.yml)

A .NET loader for Grand Theft Auto games that enables loading and execution of .NET assemblies as game plugins.

## Building

### Prerequisites
- Visual Studio 2022 with C++/CLI support
- .NET 8.0 SDK
- Plugin SDK for the target GTA game
- vcpkg for C++ dependencies

### GitHub Actions CI
This project includes GitHub Actions workflow for automated building on Windows. The CI system:
- Builds all .NET projects (Abstractions, Runtime)
- Compiles C++/CLI loader for all GTA variants (SA, VC, III)
- Uses dummy Plugin SDK headers for compilation testing
- Supports vcpkg dependency management

### Manual Build
1. Install the Plugin SDK and set the `PLUGIN_SDK_DIR` environment variable
2. Install vcpkg dependencies: `vcpkg install`
3. Open `project_files/Megasware128.GTA.DotNetLoader.sln` in Visual Studio
4. Build the solution for your target GTA game variant