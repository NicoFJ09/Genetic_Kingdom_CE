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
    src/screens/DefeatScreen.cpp
    src/screens/ScreenManager.cpp
    src/core/EconomySystem.cpp
    src/core/Game.cpp
    src/core/WaveManager.cpp
    src/systems/Pathfinding.cpp
    src/systems/GeneticAlgorithm.cpp
    src/ui/Button.cpp
    src/ui/TextElement.cpp
    src/ui/GamePanel.cpp
    src/ui/BottomPanel.cpp
    src/ui/SidePanel.cpp
    src/ui/TowerBuy.cpp
    src/ui/TowerUpgrade.cpp
    src/entities/enemies/ogre/Ogre.cpp
    src/entities/enemies/harpy/Harpy.cpp
    src/entities/enemies/mercenary/Mercenary.cpp
    src/entities/enemies/darkElf/DarkElf.cpp
    src/entities/enemies/Enemy.cpp
    src/entities/towers/Tower.cpp
    src/entities/towers/archerTower/ArcherTower.cpp
    src/entities/towers/mageTower/MageTower.cpp
    src/entities/towers/artilleryTower/ArtilleryTower.cpp
    src/map/Map.cpp
    src/map/Tile.cpp
    src/map/PathTile.cpp
    src/map/GrassTile.cpp  
    src/map/TowerTile.cpp
    src/map/BridgeTile.cpp
    src/utils/Timer.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARIES})

# Add compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${RAYLIB_CFLAGS_OTHER})