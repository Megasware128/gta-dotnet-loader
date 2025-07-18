#!/bin/bash

# Linux Build Setup Script for GTA .NET Loader
# This script helps set up the development environment on Linux

set -e

echo "🔧 Setting up GTA .NET Loader development environment on Linux..."

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if running on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    print_error "This script is designed for Linux systems only."
    exit 1
fi

# Update package list
print_status "Updating package list..."
sudo apt update

# Install build essentials
print_status "Installing build essentials..."
sudo apt install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl

# Install .NET 8 if not present
if ! command -v dotnet &> /dev/null; then
    print_status "Installing .NET 8 SDK..."
    wget https://packages.microsoft.com/config/ubuntu/$(lsb_release -rs)/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
    sudo dpkg -i packages-microsoft-prod.deb
    rm packages-microsoft-prod.deb
    sudo apt update
    sudo apt install -y dotnet-sdk-8.0
else
    print_success ".NET SDK already installed: $(dotnet --version)"
fi

# Note: MinGW installation removed since C++/CLI cross-compilation isn't practical

# Install vcpkg if not present
if [ ! -d "vcpkg" ]; then
    print_status "Installing vcpkg package manager..."
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    cd ..
    print_success "vcpkg installed successfully"
else
    print_success "vcpkg already present"
fi

# Install project dependencies via vcpkg
if [ -f "vcpkg.json" ]; then
    print_status "Installing vcpkg dependencies..."
    ./vcpkg/vcpkg install --triplet=x64-linux
    print_success "vcpkg dependencies installed"
fi

# Build .NET components to verify setup
print_status "Building .NET components to verify setup..."
dotnet restore
dotnet build Megasware128.GTA.Abstractions/Megasware128.GTA.Abstractions.csproj
dotnet build Megasware128.GTA.Runtime/Megasware128.GTA.Runtime.csproj
dotnet build SamplePlugin/SamplePlugin.csproj

print_success ".NET components built successfully!"

# Create build shortcuts
print_status "Creating build shortcuts..."

cat > build.sh << 'EOF'
#!/bin/bash
# Quick build script for GTA .NET Loader

echo "🔨 Building GTA .NET Loader (.NET Components)"

# Build .NET components
echo "Building .NET components..."
dotnet build Megasware128.GTA.Abstractions/Megasware128.GTA.Abstractions.csproj -c Release
dotnet build Megasware128.GTA.Runtime/Megasware128.GTA.Runtime.csproj -c Release
dotnet build SamplePlugin/SamplePlugin.csproj -c Release

echo "✅ .NET components built successfully!"
echo ""
echo "⚠️  Note: For the complete project (including .asi files):"
echo "   Use Windows with Visual Studio and the existing premake5 system"
echo ""
echo "Output locations:"
echo "  • Abstractions: Megasware128.GTA.Abstractions/bin/Release/net8.0/"
echo "  • Runtime: Megasware128.GTA.Runtime/bin/Release/net8.0/"
echo "  • SamplePlugin: SamplePlugin/bin/Release/net8.0/"
EOF

chmod +x build.sh

print_success "Build setup completed!"

echo ""
echo "🎉 Linux development environment is ready!"
echo ""
echo "✅ What works on Linux:"
echo "  • Full .NET development (C# projects)"
echo "  • Code editing, testing, debugging"
echo "  • Package management and dependencies"
echo ""
echo "⚠️  What requires Windows:"
echo "  • Native C++/CLI component compilation"
echo "  • Final .asi file generation"
echo "  • Complete project building"
echo ""
echo "🚀 Recommended workflow:"
echo "  1. Develop .NET components on Linux: make dotnet-components"
echo "  2. Test .NET logic: make dotnet-test"  
echo "  3. For native changes: Use Windows environment"
echo "  4. Final integration: Build complete project on Windows"
echo ""
echo "Quick commands:"
echo "  • make                 - Build .NET components"
echo "  • make dev-workflow    - Show development workflow"
echo "  • make help           - See all available commands"