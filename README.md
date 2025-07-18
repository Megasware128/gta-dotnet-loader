# Megasware128.GTA.DotNetLoader

A .NET loader for Grand Theft Auto games that enables loading .NET assemblies as game plugins.

## Platform Support

- **Windows**: Full compilation support using Visual Studio and premake5
- **Linux**: .NET component development and testing (see [BUILD-LINUX.md](BUILD-LINUX.md))

## Building

### Windows (Complete Build)
```bash
premake5 vs2022
# Open in Visual Studio and build
```

### Linux (.NET Development)
```bash
# Quick setup
./setup-linux.sh

# Build .NET components
make

# See all options
make help
```

For complete Linux instructions, see [BUILD-LINUX.md](BUILD-LINUX.md).

## Project Structure

- `Megasware128.GTA.Abstractions/` - Core interfaces and abstractions
- `Megasware128.GTA.Runtime/` - Runtime system and plugin loading
- `SamplePlugin/` - Example plugin implementation
- `source/` - Native C++/CLI loader component

## Development

The project consists of both managed (.NET) and native (C++/CLI) components:

- **Managed components** can be developed on both Windows and Linux
- **Native component** requires Windows with Visual Studio for compilation
- **Final integration** requires Windows for complete .asi plugin generation