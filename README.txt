#####################################################################################
########## Tower Defense Game - Compilation Instructions for Windows 64bits #########
#####################################################################################

Follow these steps to set up the development environment and compile the game:

1. Install C++ Compiler

To compile the project, you need a C++ compiler. Install MSYS2 (which provides a MinGW-w64 compiler) by following these steps:

    - Download and install MSYS2.

    - After installation, open MSYS2 MSYS terminal.

    - Update the package database and core system packages:
            pacman -Syu
    
    - Restart the MSYS2 terminal after updating.

    - Install the required tools and libraries:
            pacman -S base-devel mingw-w64-x86_64-toolchain cmake

    - This will install gcc, g++, make, and cmake.

2. Install SFML

Next, you need to install SFML (Simple and Fast Multimedia Library).

    - In the MSYS2 terminal, run the following command to install SFML:
            pacman -S mingw-w64-x86_64-sfml
    
    - This will install SFML and the necessary dependencies.

    - Ensure that the path to the SFML DLLs (C:/msys64/mingw64/bin) is correctly set. This ensures that the runtime linker can locate the DLLs.
    - Ensure that SFML are found from cmake path (C:/msys64/mingw64/lib/cmake/sfml)
        - Else, in CMakeLists.txt file, line below must be set to the correct path
                set(SFML_DIR "C:/msys64/mingw64/lib/cmake/sfml")

3. Set Up the Project with CMake

    - Open a terminal in the project directory.

    - Create a build directory and navigate into it:
            mkdir build
            cd build

    - Run CMake to generate the build system:
            cmake ..

    - This will configure the project and detect the necessary SFML installation.

4. Build the Project

    - After CMake finishes, use the following command to compile the project:
            cmake --build . --clean-first

    - This will build the project and create the executable.

5. Run the Game

To run the game, navigate to the build directory and execute the program:

    - Run the game executable:
            ./Tower_Defense_Windows.exe