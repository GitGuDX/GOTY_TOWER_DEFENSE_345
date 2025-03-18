# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Tower_Defense)

# Set the C++ standard to C++11 (or higher)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable all warnings for better code quality (optional)
if(MSVC)
    # For Visual Studio (MSVC compiler), enable some useful warnings
    add_compile_options(/W4)
else()
    # For GCC/Clang, enable all warnings and treat them as errors
    add_compile_options(-Wall -Wextra -Werror)
endif()

# Automatically detect the platform and set compiler-specific flags (if needed)
if(WIN32)
    # Set platform-specific flags for Windows
    message(STATUS "Configuring for Windows")
    set(EXECUTABLE_NAME Tower_Defense_Windows)  # Set the name for Windows
elseif(APPLE)
    # Set platform-specific flags for macOS
    message(STATUS "Configuring for macOS")
    set(EXECUTABLE_NAME Tower_Defense_macOS)  # Set the name for macOS
elseif(UNIX)
    # Set platform-specific flags for Linux/Unix
    message(STATUS "Configuring for Linux/Unix")
    set(EXECUTABLE_NAME Tower_Defense_Linux)  # Set the name for Linux
endif()


# Find the SFML package (adjusted for any version)
find_package(SFML 2 REQUIRED COMPONENTS system window graphics audio)
# Ensure SFML include directory is set
include_directories(${SFML_INCLUDE_DIR} /opt/homebrew/opt/sfml@2/include)

# Collect all .cpp files in the src directory
file(GLOB SOURCES src/*.cpp src/GUI/*.cpp src/Views/*.cpp src/Entities/*.cpp src/EntityManagers/*.cpp src/Generators/*.cpp)  # Recursively grab all .cpp files

# Add your source files (adjust based on your project structure)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link SFML libraries (adjust to match your needed components)
#target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system X11 Xrandr Xcursor stdc++ m)

# Link SFML libraries (adjust the version and names based on your installed version)
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)
    # Specify the location of SFMLConfig.cmake
    set(SFML_DIR "C:/msys64/mingw64/lib/cmake/sfml")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)
elseif(APPLE)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)
    set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
endif()

# For Linux/Unix, link additional libraries if needed
# if(UNIX)
#     target_link_libraries(${EXECUTABLE_NAME}
#         stdc++     # Standard C++ library
#         m          # Math library
#         X11        # X11 library
#         Xrandr     # X RandR library
#         Xcursor    # X cursor library
#     )
# endif()

# Set up include directories (specifically SFML includes from the src/include folder)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

# Optionally, set up include directories if needed (for fonts, images, etc.)
# target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Add custom configurations or handle platform-specific paths if needed
