cmake_minimum_required(VERSION 3.20)

# Project configuration
project(Megasware128.GTA.DotNetLoader LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect platform and set cross-compilation if needed
if(UNIX AND NOT APPLE)
    message(STATUS "Building on Linux")
    set(BUILDING_ON_LINUX TRUE)
    
    # Set up cross-compilation for Windows target
    if(NOT CMAKE_TOOLCHAIN_FILE)
        message(STATUS "Setting up MinGW cross-compilation")
        set(CMAKE_SYSTEM_NAME Windows)
        set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
        set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
        set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
        set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    endif()
endif()

# Define configurations that match premake setup
set(CMAKE_CONFIGURATION_TYPES "ReleaseSA;DebugSA;ReleaseVC;DebugVC;ReleaseIII;DebugIII" CACHE STRING "" FORCE)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "ReleaseSA" CACHE STRING "Choose the type of build" FORCE)
endif()

# Output directories to match premake structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/asi)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/asi)

# Game-specific settings based on configuration
if(CMAKE_BUILD_TYPE MATCHES ".*SA")
    set(GAME_TARGET "SA")
    set(OUTPUT_SUFFIX "SA")
    add_definitions(-DGTASA -DPLUGIN_SGV_10US -DRW)
elseif(CMAKE_BUILD_TYPE MATCHES ".*VC")
    set(GAME_TARGET "VC")
    set(OUTPUT_SUFFIX "VC")
    add_definitions(-DGTAVC -DPLUGIN_SGV_10EN -DRW)
elseif(CMAKE_BUILD_TYPE MATCHES ".*III")
    set(GAME_TARGET "III")
    set(OUTPUT_SUFFIX "III")
    add_definitions(-DGTA3 -DPLUGIN_SGV_10EN -DRW)
endif()

# Debug/Release specific settings
if(CMAKE_BUILD_TYPE MATCHES "Debug.*")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    add_definitions(-DNDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Common definitions
add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_CRT_NON_CONFORMING_SWPRINTFS
    -D_USE_MATH_DEFINES
    -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
)

# Set character set
if(CMAKE_BUILD_TYPE MATCHES ".*SA")
    # SA uses MBCS
    add_definitions(-D_MBCS)
else()
    # VC and III use Unicode
    add_definitions(-DUNICODE -D_UNICODE)
endif()

# Source files
file(GLOB SOURCE_FILES
    "source/*.cpp"
    "source/*.h"
)

# Create the main library
add_library(${PROJECT_NAME}${OUTPUT_SUFFIX} SHARED ${SOURCE_FILES})

# Set output name and extension
set_target_properties(${PROJECT_NAME}${OUTPUT_SUFFIX} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}${OUTPUT_SUFFIX}"
    SUFFIX ".asi"
    PREFIX ""
)

# Include directories - using fallback paths for Linux builds
target_include_directories(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE
    source/
)

# Platform-specific include directories
if(BUILDING_ON_LINUX)
    # For Linux builds, we'll need to provide alternative headers or skip certain includes
    message(STATUS "Linux build detected - some Windows-specific features may be disabled")
    
    # Try to find vcpkg includes if available
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed")
        target_include_directories(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/include"
        )
    endif()
else()
    # Windows-specific includes (when building on Windows)
    target_include_directories(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE
        "$ENV{PLUGIN_SDK_DIR}/shared/"
        "$ENV{PLUGIN_SDK_DIR}/shared/game/"
        "$ENV{PLUGIN_SDK_DIR}/plugin_${GAME_TARGET}/"
        "$ENV{PLUGIN_SDK_DIR}/plugin_${GAME_TARGET}/game_${GAME_TARGET}/"
        "vcpkg_installed/x86-windows/include/"
    )
    
    # Windows-specific library directories
    target_link_directories(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE
        "$ENV{PLUGIN_SDK_DIR}/output/lib/"
        "$ENV{DXSDK_DIR}/Lib/x86/"
        "$ENV{PLUGIN_SDK_DIR}/shared/bass/"
    )
endif()

# Find and link .NET dependencies
find_package(PkgConfig QUIET)

# Try to find .NET runtime for linking
if(BUILDING_ON_LINUX)
    # For cross-compilation, we'll need to handle .NET differently
    message(STATUS "Cross-compilation detected - .NET linking may require manual configuration")
    
    # For now, we'll try to build without .NET integration on Linux
    # This is a limitation that would need to be addressed for full functionality
    add_definitions(-DLINUX_BUILD_NO_DOTNET)
else()
    # Windows .NET linking
    target_link_libraries(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE
        Megasware128.GTA.Runtime
    )
endif()

# Game-specific libraries
if(NOT BUILDING_ON_LINUX)
    if(CMAKE_BUILD_TYPE MATCHES "Debug.*")
        set(PLUGIN_LIB_SUFFIX "_d")
    else()
        set(PLUGIN_LIB_SUFFIX "")
    endif()
    
    if(GAME_TARGET STREQUAL "SA")
        target_link_libraries(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE "plugin${PLUGIN_LIB_SUFFIX}")
    elseif(GAME_TARGET STREQUAL "VC")
        target_link_libraries(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE "plugin_vc${PLUGIN_LIB_SUFFIX}")
    elseif(GAME_TARGET STREQUAL "III")
        target_link_libraries(${PROJECT_NAME}${OUTPUT_SUFFIX} PRIVATE "plugin_iii${PLUGIN_LIB_SUFFIX}")
    endif()
endif()

# Install rules
install(TARGETS ${PROJECT_NAME}${OUTPUT_SUFFIX}
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Print configuration info
message(STATUS "Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "Game Target: ${GAME_TARGET}")
message(STATUS "Output Name: ${PROJECT_NAME}${OUTPUT_SUFFIX}.asi")
message(STATUS "Building on Linux: ${BUILDING_ON_LINUX}")