#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
#include <string>
#include <array>
#include <vector>
#include <utility>
#include <unordered_map>
// Colores globales
static const Color OLIVE_DRAB = (Color){150, 154, 71, 255};         // #B4B854
static const Color OLIVE_GREEN = (Color){180, 184, 84, 255};         // #B4B854
static const Color RUST_ORANGE = (Color){200, 130, 80, 255};         // #C88250
static const Color PEACH_ORANGE = (Color){235, 150, 97, 255};        // #EB9661
static const Color APRICOT = (Color){245, 170, 110, 255};            // #F5AA6E
static const Color LIGHT_TANGERINE = (Color){255, 190, 130, 255};    // #FFBE82
static const Color GOLDENROD = (Color){218, 165, 32, 255};            //rgb(218, 165, 32)

// Dimensiones de la pantalla
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 768;

// Tipografías
static const std::string Romulus = "../assets/fonts/romulus.png";

// Mapa del juego
static const std::array<std::array<int, 31>, 19> GAME_MAP = {{
    {{2,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
    {{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1}},
    {{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,1,1,1}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0}},
    {{1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0}},
    {{1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0}},
    {{1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0}},
    {{1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0}},
    {{1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,3}}
}};

struct TowerInfo {
    std::string name;
    int costLevel1;
    int costLevel2;
    int costLevel3;
};

static const std::array<TowerInfo, 3> Towers = {{
    {"Archer Tower", 100, 75, 125},
    {"Artillery Tower", 250, 125, 175},
    {"Mage Tower", 175, 100, 150}
}};

struct EnemyInfo {
    std::string name;
    int value;
};

static const std::array<EnemyInfo, 4> EnemiesValue = {{
    {"Ogre", 25},
    {"Dark Elf", 30},
    {"Harpy", 35},
    {"Mercenary", 45}
}};

// Sprites de las torres por nivel
static const std::string ARCHER_TOWER_LVL1 = "../assets/textures/towers/towersInLayout/ArcherLOLvl1.png";
static const std::string ARCHER_TOWER_LVL2 = "../assets/textures/towers/towersInLayout/ArcherLOLvl2.png";
static const std::string ARCHER_TOWER_LVL3 = "../assets/textures/towers/towersInLayout/ArcherLOLvl3.png";

static const std::string ARTILLERY_TOWER_LVL1 = "../assets/textures/towers/towersInLayout/ArtilleryLOLvl1.png";
static const std::string ARTILLERY_TOWER_LVL2 = "../assets/textures/towers/towersInLayout/ArtilleryLOLvl2.png";
static const std::string ARTILLERY_TOWER_LVL3 = "../assets/textures/towers/towersInLayout/ArtilleryLOLvl3.png";

static const std::string MAGE_TOWER_LVL1 = "../assets/textures/towers/towersInLayout/MageLOLvl1.png";
static const std::string MAGE_TOWER_LVL2 = "../assets/textures/towers/towersInLayout/MageLOLvl2.png";
static const std::string MAGE_TOWER_LVL3 = "../assets/textures/towers/towersInLayout/MageLOLvl3.png";

// Asset paths:
static const std::string MAP_PATH = "../assets/map/tiles/";

static const std::unordered_map<std::string, std::string> ENEMY_SPRITE_PATHS = {
    {"Ogre", "../assets/textures/enemies/ogre/Ogre.png"},
    {"Dark Elf", "../assets/textures/enemies/darkelf/DarkElf.png"},
    {"Harpy", "../assets/textures/enemies/harpy/Harpy.png"},
    {"Mercenary", "../assets/textures/enemies/mercenary/Mercenary.png"}
};


#endif // CONSTANTS_H