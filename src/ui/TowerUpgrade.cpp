#include "TowerUpgrade.h"
#include "../config/Constants.h"

TowerUpgrade::TowerUpgrade(float panelX, float panelY, float panelWidth, float panelHeight, EconomySystem& economySystem)
    : isVisible(false), economySystem(economySystem), bounds({panelX, panelY, panelWidth, panelHeight}) {
    LoadTowerTextures();
}

TowerUpgrade::~TowerUpgrade() {
    // Liberar todas las texturas cargadas
    for (auto& type : towerTextures) {
        for (auto& level : type.second) {
            UnloadTexture(level.second);
        }
    }
}

void TowerUpgrade::LoadTowerTextures() {
    // Cargar texturas para cada tipo de torre y nivel
    towerTextures["Mage Tower"][1] = LoadTexture("../assets/textures/towers/towersInLayout/MageLOLvl1.png");
    towerTextures["Mage Tower"][2] = LoadTexture("../assets/textures/towers/towersInLayout/MageLOLvl2.png");
    towerTextures["Mage Tower"][3] = LoadTexture("../assets/textures/towers/towersInLayout/MageLOLvl3.png");

    towerTextures["Archer Tower"][1] = LoadTexture("../assets/textures/towers/towersInLayout/ArcherLOLvl1.png");
    towerTextures["Archer Tower"][2] = LoadTexture("../assets/textures/towers/towersInLayout/ArcherLOLvl2.png");
    towerTextures["Archer Tower"][3] = LoadTexture("../assets/textures/towers/towersInLayout/ArcherLOLvl3.png");

    towerTextures["Artillery Tower"][1] = LoadTexture("../assets/textures/towers/towersInLayout/ArtilleryLOLvl1.png");
    towerTextures["Artillery Tower"][2] = LoadTexture("../assets/textures/towers/towersInLayout/ArtilleryLOLvl2.png");
    towerTextures["Artillery Tower"][3] = LoadTexture("../assets/textures/towers/towersInLayout/ArtilleryLOLvl3.png");
}

void TowerUpgrade::Update(TowerTile*& selectedTower) {
    // Mostrar u ocultar la UI según si hay una torre seleccionada
    isVisible = (selectedTower != nullptr);

    if (isVisible) {
        HandleUpgrade(selectedTower); // Manejar la lógica de mejora
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

    // Dibujar la vista previa de la torre centrada en el panel
    Texture2D previewTexture = towerTextures[tower->GetTowerType()][tower->GetLevel()];
    float previewWidth = previewTexture.width / 2.0f; // Reducir a la mitad
    float previewHeight = previewTexture.height / 2.0f; // Reducir a la mitad
    float previewX = bounds.x + (bounds.width / 2) - (previewWidth / 2); // Centrar horizontalmente
    float previewY = bounds.y + (bounds.height / 2) - (previewHeight / 2); // Centrar verticalmente
    DrawTextureEx(previewTexture, {previewX, previewY}, 0.0f, 0.5f, WHITE); // Dibujar con escala 0.5

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
    
    // Calcular y mostrar el costo de mejora
    int upgradeCost = 0;
    for (const auto& towerInfo : Towers) {
        if (towerInfo.name == tower->GetTowerType()) {
            // Seleccionar el costo según el nivel actual de la torre
            if (tower->GetLevel() == 1) {
                upgradeCost = towerInfo.costLevel2;
            } else if (tower->GetLevel() == 2) {
                upgradeCost = towerInfo.costLevel3;
            } else {
                upgradeCost = 0; // Nivel máximo, no hay más mejoras
            }
            break;
        }
    }
    
    if (upgradeCost > 0) {
        const char* costText = TextFormat("Cost: %d", upgradeCost);
        int costTextWidth = MeasureText(costText, fontSize);
        float costTextX = upgradeButton.x - costTextWidth - 10; // 10px a la izquierda del botón
        float costTextY = upgradeButton.y + (upgradeButton.height - fontSize) / 2; // Centrado verticalmente con el botón
        
        // Color del texto según si el jugador tiene suficiente dinero
        Color costColor = (economySystem.GetBalance() >= upgradeCost) ? GREEN : RED;
        DrawText(costText, costTextX, costTextY, fontSize, costColor);
    } else if (tower->GetLevel() >= 3) {
        // Si la torre está al nivel máximo, mostrar un mensaje
        const char* maxLevelText = "Max Level";
        int maxLevelTextWidth = MeasureText(maxLevelText, fontSize);
        float maxLevelTextX = upgradeButton.x - maxLevelTextWidth - 10;
        float maxLevelTextY = upgradeButton.y + (upgradeButton.height - fontSize) / 2;
        DrawText(maxLevelText, maxLevelTextX, maxLevelTextY, fontSize, GOLD);
    }
}


void TowerUpgrade::HandleUpgrade(TowerTile*& selectedTower) {
    if (!selectedTower) return;

    Tower* tower = selectedTower->GetTower();
    if (!tower) return;

    // Buscar el costo de mejora basado en el tipo de torre
    int upgradeCost = 0;
    for (const auto& towerInfo : Towers) {
        if (towerInfo.name == tower->GetTowerType()) {
            // Seleccionar el costo según el nivel actual de la torre
            if (tower->GetLevel() == 1) {
                upgradeCost = towerInfo.costLevel2;
            } else if (tower->GetLevel() == 2) {
                upgradeCost = towerInfo.costLevel3;
            } else {
                return; // No se puede mejorar más
            }
            break;
        }
    }

    // Si no se encontró el tipo de torre, salir
    if (upgradeCost == 0) {
        TraceLog(LOG_WARNING, "Tower type not found in Towers array.");
        return;
    }

    // Dibujar el botón de mejora
    Rectangle upgradeButton = {bounds.x + bounds.width - 120, bounds.y + 80, 100, 40};

    // Verificar si el jugador tiene suficiente balance y manejar la interacción
    if (CheckCollisionPointRec(GetMousePosition(), upgradeButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isButtonPressed) {
            isButtonPressed = true; // Marcar el botón como presionado
            if (economySystem.GetBalance() >= upgradeCost) {
                economySystem.DecreaseFromBalance(upgradeCost); // Reducir el balance
                tower->LevelUp(); // Subir de nivel la torre
                TraceLog(LOG_INFO, "Tower upgraded successfully!");
            } else {
                TraceLog(LOG_WARNING, "Not enough balance to upgrade tower.");
            }
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isButtonPressed = false; // Liberar el estado del botón
        }
    }
}