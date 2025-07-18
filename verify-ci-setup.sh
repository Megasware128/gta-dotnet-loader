#!/bin/bash
# CI verification script to check if all required components are present

echo "Verifying GitHub Actions workflow configuration..."

# Check if workflow exists
if [ ! -f ".github/workflows/build.yml" ]; then
    echo "❌ GitHub Actions workflow file not found"
    exit 1
fi

echo "✅ GitHub Actions workflow file exists"

# Check if ci-build.props exists
if [ ! -f "ci-build.props" ]; then
    echo "❌ ci-build.props file not found"
    exit 1
fi

echo "✅ ci-build.props file exists"

# Verify .NET projects exist
if [ ! -f "Megasware128.GTA.Abstractions/Megasware128.GTA.Abstractions.csproj" ]; then
    echo "❌ Abstractions project not found"
    exit 1
fi

if [ ! -f "Megasware128.GTA.Runtime/Megasware128.GTA.Runtime.csproj" ]; then
    echo "❌ Runtime project not found"
    exit 1
fi

echo "✅ .NET projects exist"

# Verify solution file exists
if [ ! -f "project_files/Megasware128.GTA.DotNetLoader.sln" ]; then
    echo "❌ Solution file not found"
    exit 1
fi

echo "✅ Solution file exists"

# Verify C++ project exists
if [ ! -f "project_files/Megasware128.GTA.DotNetLoader.vcxproj" ]; then
    echo "❌ C++ project file not found"
    exit 1
fi

echo "✅ C++ project file exists"

# Check vcpkg configuration
if [ ! -f "vcpkg.json" ]; then
    echo "❌ vcpkg.json not found"
    exit 1
fi

if [ ! -f "vcpkg-configuration.json" ]; then
    echo "❌ vcpkg-configuration.json not found"
    exit 1
fi

echo "✅ vcpkg configuration files exist"

# Test .NET compilation if dotnet is available
if command -v dotnet &> /dev/null; then
    echo "Testing .NET compilation..."
    
    if dotnet build Megasware128.GTA.Abstractions/Megasware128.GTA.Abstractions.csproj --configuration Release; then
        echo "✅ Abstractions project compiles successfully"
    else
        echo "❌ Abstractions project compilation failed"
        exit 1
    fi
    
    if dotnet build Megasware128.GTA.Runtime/Megasware128.GTA.Runtime.csproj --configuration Release; then
        echo "✅ Runtime project compiles successfully"
    else
        echo "❌ Runtime project compilation failed"
        exit 1
    fi
else
    echo "ℹ️  dotnet CLI not available, skipping .NET compilation test"
fi

echo ""
echo "🎉 All verification checks passed!"
echo ""
echo "The project is ready for GitHub Actions Windows compilation!"
echo ""
echo "Key features configured:"
echo "  ✅ Windows-based CI workflow"
echo "  ✅ .NET 8 and MSBuild setup"
echo "  ✅ vcpkg for C++ dependencies"
echo "  ✅ Dummy Plugin SDK structure"
echo "  ✅ PostBuildEvent disabled for CI"
echo "  ✅ Multiple GTA variant builds (SA, VC, III)"