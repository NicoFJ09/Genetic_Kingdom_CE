#include "GamePanel.h"
#include "../config/Constants.h"

GamePanel::GamePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}) {
    // Load the map data from GAME_MAP into the Map class
    map.LoadFromArray(GAME_MAP);
}

void GamePanel::Update() {
    // Delegate hover detection to the map
    map.CheckHover();
    map.HandleClick(); 
}

void GamePanel::Draw() {
    // Draw the panel background
    DrawRectangleRec(bounds, OLIVE_GREEN);

    // Draw the map
    map.Draw();
}

Map& GamePanel::GetMap() {
    return map;
}