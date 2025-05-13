#include "SidePanel.h"
#include "../config/Constants.h"

SidePanel::SidePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}), currentWave(0), remainingTime(0.0f) {}

SidePanel::~SidePanel() {}

void SidePanel::UpdateWaveInfo(int wave, float time) {
    currentWave = wave;
    remainingTime = time;
}

void SidePanel::SetActiveEnemies(const std::vector<Enemy*>& enemies) {
    activeEnemies = enemies;
}

void SidePanel::Draw() {
    // Dibujar el fondo del panel
    DrawRectangleRec(bounds, APRICOT);

    // Dibujar la información de la ola
    int fontSize = 20;
    float textX = bounds.x + 10;
    float textY = bounds.y + 10;

    DrawText(TextFormat("Wave: %d", currentWave), textX, textY, fontSize, WHITE);
    textY += 30;
    DrawText(TextFormat("Time Remaining: %.2f", remainingTime), textX, textY, fontSize, WHITE);
    textY += 40;

    // Imprimir los datos de todos los enemigos activos
    for (Enemy* enemy : activeEnemies) {
        DrawText(TextFormat("Type: %s", enemy->GetEnemyType().c_str()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Health: %d", enemy->GetHealth()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Speed: %d", enemy->GetSpeed()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Arrow Resistance: %d", enemy->GetArrowResistance()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Magic Resistance: %d", enemy->GetMagicResistance()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Artillery Resistance: %d", enemy->GetArtilleryResistance()), textX, textY, fontSize, BLACK);
        textY += 20;
        DrawText(TextFormat("Mutated: %s", enemy->IsMutated() ? "Yes" : "No"), textX, textY, fontSize, BLACK);
        textY += 40; // Espaciado entre enemigos
    }
}