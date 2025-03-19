cmake_minimum_required(VERSION 3.10)
project(Tower_Defense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif() 

# Set executable name and SFML paths based on platform
if(WIN32)
    message(STATUS "Configuring for Windows")
    set(EXECUTABLE_NAME Tower_Defense_Windows)
elseif(APPLE)
    message(STATUS "Configuring for macOS")
    set(EXECUTABLE_NAME Tower_Defense_macOS)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(SFML_DIR "/opt/homebrew/lib/cmake/SFML")
    else()
        set(SFML_DIR "/usr/local/lib/cmake/SFML")
endif()
elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")
    set(EXECUTABLE_NAME Tower_Defense_Linux)
endif()

# Find SFML (platform-specific)
if(APPLE)
    find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
else()
    find_package(SFML REQUIRED COMPONENTS system window graphics)
endif()


# Collect all .cpp files in the src directory
file(GLOB SOURCES src/*.cpp src/GUI/*.cpp src/Views/*.cpp src/Entities/*.cpp src/EntityManagers/*.cpp src/Generators/*.cpp src/EntityDecorators/*.cpp)  # Recursively grab all .cpp files

# Add your source files (adjust based on your project structure)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link libraries
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system opengl32 gdi32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system X11 Xrandr Xcursor stdc++ m)
elseif(APPLE)
    target_link_libraries(${EXECUTABLE_NAME} 
        sfml-graphics
        sfml-window
        "-framework OpenGL"
        "-framework CoreFoundation"
    )
endif()

# Include directories
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)