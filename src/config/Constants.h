#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
#include <string>
#include <array>
#include <utility>
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
    {"Archer Tower", 100, 250, 500},
    {"Artillery Tower", 100, 250, 500},
    {"Mage Tower", 100, 250, 500}
}};


// Asset paths:
static const std::string MAP_PATH = "../assets/map/tiles/";

#endif // CONSTANTS_H