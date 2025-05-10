# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GeneticKingdom VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Raylib (assuming it's installed via pkg-config)
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Include directories for Raylib and project-specific headers
include_directories(
    ${RAYLIB_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/entities
    ${CMAKE_SOURCE_DIR}/src/entities/enemies
    ${CMAKE_SOURCE_DIR}/src/entities/enemies/ogre
    ${CMAKE_SOURCE_DIR}/src/entities/enemies/harpy
    ${CMAKE_SOURCE_DIR}/src/entities/enemies/mercenary
    ${CMAKE_SOURCE_DIR}/src/entities/enemies/darkElf
)

# Add the source files
set(SOURCES
    src/main.cpp
    src/screens/StartScreen.cpp
    src/screens/GameplayScreen.cpp
    src/screens/ScreenManager.cpp
    src/ui/Button.cpp
    src/ui/TextElement.cpp
    src/ui/GamePanel.cpp
    src/ui/BottomPanel.cpp
    src/ui/SidePanel.cpp
    src/entities/enemies/ogre/Ogre.cpp
    src/entities/enemies/harpy/Harpy.cpp
    src/entities/enemies/mercenary/Mercenary.cpp
    src/entities/enemies/darkElf/DarkElf.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARIES})

# Add compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${RAYLIB_CFLAGS_OTHER})

# Define macros (if needed)
add_definitions(-DDEBUG)

# Set IntelliSense mode (optional, for better IDE support)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)