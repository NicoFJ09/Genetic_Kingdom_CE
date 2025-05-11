#include "TowerBuy.h"
#include "../config/Constants.h"

TowerBuy::TowerBuy(Map& map, EconomySystem& economySystem, float panelX, float panelY, float panelWidth, float panelHeight)
    : map(map), economySystem(economySystem), selectedTowerIndex(-1), buyButtonEnabled(false), isVisible(false) {
    // Ajustar las dimensiones de los cuadrados de torres
    float squareWidth = 100;
    float squareHeight = 116;
    float labelHeight = 20; // Altura del texto de las etiquetas

    // Limitar el ancho total a dos tercios del ancho del panel
    float usableWidth = panelWidth * (2.0f / 3.0f);

    // Calcular el espaciado para que los cuadrados estén equidistantes dentro del área usable
    size_t numSquares = towerSquares.size();
    float totalSquaresWidth = numSquares * squareWidth;
    float totalSpacingWidth = usableWidth - totalSquaresWidth;
    float spacing = totalSpacingWidth / (numSquares + 1); // Espaciado entre cuadrados

    // Posición inicial en Y para los cuadrados (centrados verticalmente en el panel)
    float totalHeight = squareHeight + labelHeight + 10; // Altura de los cuadrados + etiquetas + padding
    float initialY = panelY + (panelHeight - totalHeight) / 2;

    // Inicializar los cuadrados de torres dentro del área usable
    for (size_t i = 0; i < numSquares; ++i) {
        float squareX = panelX + spacing + i * (squareWidth + spacing);
        towerSquares[i] = {squareX, initialY, squareWidth, squareHeight};
    }

    // Mantener el botón de compra en su posición actual
    buyButton = {panelX + panelWidth - 120, panelY + 80, 100, 40};
}

void TowerBuy::Update(GrassTile*& selectedTile) {
    // Mostrar u ocultar la UI según si hay un tile seleccionado
    isVisible = (selectedTile != nullptr);

    if (isVisible) {
        HandleSelectTower();
        HandleBuy(selectedTile);
    }
}

void TowerBuy::Draw() {
    if (!isVisible) return; // No dibujar si la UI no está visible

    // Dibujar los bordes de los cuadrados de torres y sus etiquetas
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        // Dibujar el contorno del cuadrado
        Color outlineColor = (selectedTowerIndex == (int)i) ? WHITE : BLACK;
        DrawRectangleLinesEx(towerSquares[i], 2, outlineColor);

        // Dibujar la etiqueta debajo del cuadrado
        const char* labelText = Towers[i].name.c_str();
        int fontSize = 12;
        int textWidth = MeasureText(labelText, fontSize);
        float textX = towerSquares[i].x + (towerSquares[i].width - textWidth) / 2;
        float textY = towerSquares[i].y + towerSquares[i].height + 5; // Debajo del cuadrado
        DrawText(labelText, textX, textY, fontSize, WHITE);
    }

    // Dibujar el botón de compra
    Color buyColor = buyButtonEnabled ? RUST_ORANGE : GRAY;
    DrawRectangleRec(buyButton, buyColor);
    DrawRectangleLinesEx(buyButton, 2, BLACK);

    // Centrar el texto "Buy" en el botón
    const char* buttonText = "Buy";
    int fontSize = 20;
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize; // Aproximación: la altura del texto es igual al tamaño de la fuente
    float textX = buyButton.x + (buyButton.width - textWidth) / 2;
    float textY = buyButton.y + (buyButton.height - textHeight) / 2;

    DrawText(buttonText, textX, textY, fontSize, WHITE);
}

void TowerBuy::HandleSelectTower() {
    for (size_t i = 0; i < towerSquares.size(); ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), towerSquares[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedTowerIndex = i; // Seleccionar la torre
        }
    }
}

void TowerBuy::HandleBuy(GrassTile*& selectedTile) {
    if (selectedTowerIndex != -1) {
        const TowerInfo& tower = Towers[selectedTowerIndex];
        int cost = tower.costLevel1; // Usar el costo del nivel 1 como ejemplo

        // Habilitar o deshabilitar el botón de compra según el balance
        buyButtonEnabled = (economySystem.GetBalance() >= cost);

        if (buyButtonEnabled && CheckCollisionPointRec(GetMousePosition(), buyButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            economySystem.DecreaseFromBalance(cost); // Reducir el balance
            TraceLog(LOG_INFO, "Bought: %s", tower.name.c_str()); // Imprimir mensaje

            // Reemplazar el tile seleccionado con un TowerTile que tenga la torre específica
            TowerTile* newTile = map.ReplaceTileWithTower(selectedTile, tower.name, 1); // Nivel inicial 1

            // Imprimir las características de la torre desde el TowerTile
            if (newTile) {
                Tower* placedTower = newTile->GetTower();
                if (placedTower) {
                    TraceLog(LOG_INFO, "Tower Type: %s", placedTower->GetTowerType().c_str());
                    TraceLog(LOG_INFO, "Position: (%.2f, %.2f)", placedTower->GetPosition().x, placedTower->GetPosition().y);
                    TraceLog(LOG_INFO, "Level: %d", placedTower->GetLevel());
                    TraceLog(LOG_INFO, "Damage: %d", placedTower->GetDamage());
                    TraceLog(LOG_INFO, "Speed: %d", placedTower->GetSpeed());
                    TraceLog(LOG_INFO, "Range: %d", placedTower->GetRange());
                    TraceLog(LOG_INFO, "Attack Regeneration Time: %d", placedTower->GetAttackRegenerationTime());
                    TraceLog(LOG_INFO, "Special Attack Regeneration Time: %d", placedTower->GetSpecialAttackRegenerationTime());
                } else {
                    TraceLog(LOG_ERROR, "No tower instance available.");
                }

            // Reiniciar la selección y deshabilitar los botones
            selectedTile = nullptr;
            selectedTowerIndex = -1;
            buyButtonEnabled = false;
        }
    } else {
        buyButtonEnabled = false; // Deshabilitar el botón si no hay torre seleccionada
    }
}
}