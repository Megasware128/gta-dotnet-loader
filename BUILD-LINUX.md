# Building on Linux

This project can be partially compiled on Linux. The .NET components (C#) can be fully developed and built on Linux, while the native C++/CLI component requires a Windows environment for compilation.

## What Works on Linux ✅

- **Full .NET development**: All C# projects build and run perfectly
- **Code editing and testing**: Complete development workflow for managed code
- **Package management**: NuGet and dependency management
- **Plugin development**: Create and test plugin logic

## What Requires Windows ⚠️

- **Native component compilation**: The C++/CLI mixed-mode code requires MSVC
- **Final .asi generation**: ASI plugin files need Windows build environment
- **Complete project building**: Full integration requires Windows toolchain

## Quick Setup

1. **Automated Setup** (Recommended):
   ```bash
   ./setup-linux.sh
   ```

2. **Manual Setup**:
   ```bash
   # Install .NET 8 SDK
   sudo apt update
   sudo apt install -y dotnet-sdk-8.0
   
   # Build .NET components
   dotnet build Megasware128.GTA.Abstractions/
   dotnet build Megasware128.GTA.Runtime/
   dotnet build SamplePlugin/
   ```

## Building .NET Components

```bash
# Build all .NET projects
make

# Or use dotnet directly
dotnet build Megasware128.GTA.Abstractions/
dotnet build Megasware128.GTA.Runtime/
dotnet build SamplePlugin/

# Test the components
make dotnet-test
```

## Development Workflow

### Recommended Hybrid Approach:

1. **Linux Development**:
   - Edit C# code (Abstractions, Runtime, plugins)
   - Build and test .NET components: `make`
   - Debug managed code logic
   - Use any C# IDE (VS Code, JetBrains Rider, etc.)

2. **Windows Integration**:
   - Edit C++ code if needed
   - Build complete project: `premake5 vs2022` → Visual Studio
   - Generate final .asi files
   - Test in actual GTA environment

### Pure Linux Development:
If you only work on .NET components (plugins, runtime logic), you can do everything on Linux:

```bash
# Daily workflow
make                    # Build everything
make dotnet-test        # Run tests  
make format            # Format code
make check-updates     # Check for updates
```

## Available Build Commands

```bash
make                   # Build .NET components
make dotnet-test       # Test .NET components  
make clean             # Clean build artifacts
make format            # Format C# code
make package           # Create distribution packages
make help              # Show all commands
```

## Limitations

- **No native compilation**: C++/CLI requires Windows MSVC compiler
- **No .asi generation**: Final plugin files need Windows build environment
- **Limited debugging**: Can't debug native/managed interop on Linux
- **SDK dependencies**: GTA Plugin SDK and DirectX SDK are Windows-specific

## Tools and IDEs

### Recommended for Linux:
- **VS Code** with C# extension
- **JetBrains Rider** (commercial, excellent .NET support)
- **MonoDevelop/Xamarin Studio**
- Any text editor + `dotnet` CLI

### For complete development:
- **Windows VM** with Visual Studio
- **Wine + Visual Studio Build Tools** (experimental)
- **Dual-boot setup**

## Integration with Windows Build

The Linux build system is designed to coexist with the existing Windows system:

- **Windows developers**: Continue using `premake5 vs2022` + Visual Studio
- **Linux developers**: Use `make` for .NET development
- **Hybrid teams**: Develop .NET on Linux, integrate on Windows

Both approaches produce compatible outputs and can be used by the same team.