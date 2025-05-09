# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GeneticKingdom VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Raylib (assuming it's installed via pkg-config)
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Include directories for Raylib
include_directories(${RAYLIB_INCLUDE_DIRS})

# Add the source files
set(SOURCES
    src/main.cpp
    src/screens/StartScreen.cpp
    src/screens/GameplayScreen.cpp
    src/screens/ScreenManager.cpp
    src/ui/Button.cpp
    src/ui/TextElement.cpp
    # Add more .cpp files here as needed
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARIES})

# Add compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${RAYLIB_CFLAGS_OTHER})