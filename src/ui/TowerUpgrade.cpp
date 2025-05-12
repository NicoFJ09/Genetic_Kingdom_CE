#include "TowerUpgrade.h"
#include "../config/Constants.h"

TowerUpgrade::TowerUpgrade(float panelX, float panelY, float panelWidth, float panelHeight)
    : isVisible(false), bounds({panelX, panelY, panelWidth, panelHeight}) {}

void TowerUpgrade::Update(TowerTile*& selectedTower) {
    // Mostrar u ocultar la UI según si hay una torre seleccionada
    isVisible = (selectedTower != nullptr);

    if (isVisible) {
        // Aquí puedes manejar la lógica de interacción, como botones de mejora
        Rectangle upgradeButton = {bounds.x + bounds.width - 120, bounds.y + 80, 100, 40};

        if (CheckCollisionPointRec(GetMousePosition(), upgradeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (selectedTower) {
                Tower* tower = selectedTower->GetTower();
                if (tower) {
                    // Lógica para mejorar la torre
                    TraceLog(LOG_INFO, "Upgrade button clicked for tower at level %d", tower->GetLevel());
                }
            }
        }
    }
}

void TowerUpgrade::Draw(TowerTile* selectedTower) {
    if (!isVisible || !selectedTower) return;

    Tower* tower = selectedTower->GetTower();
    if (!tower) return;

    // Configuración de las posiciones relativas
    float padding = 10.0f; // Espaciado interno
    float textX = bounds.x + padding; // Posición X inicial para los textos
    float textY = bounds.y + padding; // Posición Y inicial para los textos
    int fontSize = 20; // Tamaño de fuente
    float lineSpacing = 30.0f; // Espaciado entre líneas

    // Dibujar el nombre de la torre
    DrawText(tower->GetTowerType().c_str(), textX, textY, fontSize, WHITE);
    textY += lineSpacing;

    // Dibujar las estadísticas actuales
    DrawText(TextFormat("Level: %d", tower->GetLevel()), textX, textY, fontSize, WHITE);
    textY += lineSpacing;
    DrawText(TextFormat("Damage: %d", tower->GetDamage()), textX, textY, fontSize, WHITE);
    textY += lineSpacing;
    DrawText(TextFormat("Speed: %d", tower->GetSpeed()), textX, textY, fontSize, WHITE);
    textY += lineSpacing;
    DrawText(TextFormat("Range: %d", tower->GetRange()), textX, textY, fontSize, WHITE);
    textY += lineSpacing;

    // Dibujar el botón de mejora
    Rectangle upgradeButton = {bounds.x + bounds.width - 120, bounds.y + 80, 100, 40};
    Color buttonColor = RUST_ORANGE; // Color del botón
    DrawRectangleRec(upgradeButton, buttonColor);
    DrawRectangleLinesEx(upgradeButton, 2, BLACK);

    // Centrar el texto "Upgrade" en el botón
    const char* buttonText = "Upgrade";
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize; // Aproximación: la altura del texto es igual al tamaño de la fuente
    float buttonTextX = upgradeButton.x + (upgradeButton.width - textWidth) / 2;
    float buttonTextY = upgradeButton.y + (upgradeButton.height - textHeight) / 2;

    DrawText(buttonText, buttonTextX, buttonTextY, fontSize, WHITE);
}