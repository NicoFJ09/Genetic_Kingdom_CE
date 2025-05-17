#include "SidePanel.h"
#include "../config/Constants.h"

SidePanel::SidePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}), 
      currentWave(0), 
      enemiesKilled(0), // Inicializar el contador
      currentPageIndex(0) {
    // Inicializar los tipos de enemigos desde ENEMY_SPRITE_PATHS
    for (const auto& pair : ENEMY_SPRITE_PATHS) {
        enemyTypes.push_back(pair.first);

        // Cargar la textura del enemigo y almacenarla en el mapa
        Texture2D texture = LoadTexture(pair.second.c_str());
        if (texture.id != 0) {
            enemyTextures[pair.first] = texture;
        } else {
            TraceLog(LOG_ERROR, "Failed to load texture for enemy type: %s", pair.first.c_str());
        }
    }
}

void SidePanel::SetEnemyVectors(
    const std::vector<Enemy*>& ogres,
    const std::vector<Enemy*>& harpies,
    const std::vector<Enemy*>& mercenaries,
    const std::vector<Enemy*>& darkElves) {
    
    this->ogres = ogres;
    this->harpies = harpies;
    this->mercenaries = mercenaries;
    this->darkElves = darkElves;
}

SidePanel::~SidePanel() {
    // Descargar todas las texturas almacenadas en el mapa
    for (auto& pair : enemyTextures) {
        UnloadTexture(pair.second);
    }
    enemyTextures.clear();
}

void SidePanel::UpdateWaveInfo(int wave, int killedEnemies) {
    currentWave = wave;
    enemiesKilled = killedEnemies;
}

void SidePanel::Update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // Botón de página anterior
        Rectangle prevButton = {bounds.x + 10, bounds.y + bounds.height - 40, 30, 30};
        if (CheckCollisionPointRec(mousePos, prevButton)) {
            currentPageIndex = (currentPageIndex - 1 + enemyTypes.size()) % enemyTypes.size();
        }

        // Botón de página siguiente
        Rectangle nextButton = {bounds.x + bounds.width - 40, bounds.y + bounds.height - 40, 30, 30};
        if (CheckCollisionPointRec(mousePos, nextButton)) {
            currentPageIndex = (currentPageIndex + 1) % enemyTypes.size();
        }
    }
}

void SidePanel::Draw() {
    // Dibujar el fondo del panel
    DrawRectangleRec(bounds, APRICOT);

    // Dibujar la información de la ola
    int fontSize = 20;
    float textX = bounds.x + 5;
    float textY = bounds.y + 10;

    DrawText(TextFormat("Wave: %d", currentWave), textX, textY, fontSize, WHITE);
    textY += 30;
    
    DrawText(TextFormat("Enemies killed: %d", enemiesKilled), textX, textY, fontSize, WHITE);
    textY += 30;

    // Verificar que hay tipos de enemigos definidos
    if (enemyTypes.empty() || currentPageIndex >= enemyTypes.size()) {
        DrawText("No enemy types available", bounds.x + 10, textY, fontSize, DARKGRAY);
        return;
    }

    // Obtener el tipo de enemigo actual
    const std::string& currentType = enemyTypes[currentPageIndex];

    // Seleccionar el vector adecuado según el tipo actual
    std::vector<Enemy*>* currentEnemies = nullptr;
    if (currentType == "Ogre") {
        currentEnemies = &ogres;
    } else if (currentType == "Harpy") {
        currentEnemies = &harpies;
    } else if (currentType == "Mercenary") {
        currentEnemies = &mercenaries;
    } else if (currentType == "Dark Elf") {
        currentEnemies = &darkElves;
    }

    // Verificar si hay enemigos de este tipo
    if (!currentEnemies || currentEnemies->empty()) {
        // Dibujar el título del tipo de enemigo (centrado en X)
        int typeTextWidth = MeasureText(currentType.c_str(), fontSize);
        float typeTextX = bounds.x + (bounds.width - typeTextWidth) / 2;
        DrawText(currentType.c_str(), typeTextX, textY, fontSize, BLACK);
        textY += 30;
        
        DrawText("No enemies of this type", bounds.x + 10, textY, fontSize, DARKGRAY);
        
        // Dibujar los botones de paginación aunque no haya enemigos
        DrawPaginationButtons();
        return;
    }

    // Dibujar el título del tipo de enemigo (centrado en X)
    int typeTextWidth = MeasureText(currentType.c_str(), fontSize);
    float typeTextX = bounds.x + (bounds.width - typeTextWidth) / 2;
    DrawText(currentType.c_str(), typeTextX, textY, fontSize, BLACK);
    textY += 30;

    // Obtener la generación de este tipo (del primer enemigo)
    int generation = (*currentEnemies)[0]->GetGeneration();
    std::string generationText = TextFormat("Generation: %d", generation);
    int generationTextWidth = MeasureText(generationText.c_str(), fontSize);
    float generationTextX = bounds.x + (bounds.width - generationTextWidth) / 2;
    DrawText(generationText.c_str(), generationTextX, textY, fontSize, DARKGRAY);
    textY += 30;

    // Contar mutaciones para el tipo actual
    int mutationCount = 0;
    for (Enemy* enemy : *currentEnemies) {
        if (enemy->IsMutated()) {
            mutationCount++;
        }
    }

    // Mostrar la cantidad de mutaciones debajo del número de generación
    std::string mutationText = TextFormat("Mutations: %d", mutationCount);
    int mutationTextWidth = MeasureText(mutationText.c_str(), fontSize);
    float mutationTextX = bounds.x + (bounds.width - mutationTextWidth) / 2;
    DrawText(mutationText.c_str(), mutationTextX, textY, fontSize, DARKGRAY);
    textY += 40;

    // Dibujar el sprite del enemigo (centrado en X)
    auto it = enemyTextures.find(currentType);
    if (it != enemyTextures.end()) {
        Texture2D sprite = it->second;
        float spriteX = bounds.x + (bounds.width - sprite.width) / 2;
        float spriteY = textY;
        DrawTexture(sprite, spriteX, spriteY, WHITE);
        textY += sprite.height + 20; // Espaciado debajo del sprite
    } else {
        TraceLog(LOG_WARNING, "Texture not found for enemy type: %s", currentType.c_str());
    }

    // Dibujar encabezados de la tabla
    float colX[] = {textX, textX + 50, textX + 100, textX + 150, textX + 200, textX + 250}; // Posiciones de las columnas
    DrawText("L", colX[0], textY, fontSize, BLACK);
    DrawText("S", colX[1], textY, fontSize, BLACK);
    DrawText("FR", colX[2], textY, fontSize, BLACK);
    DrawText("MR", colX[3], textY, fontSize, BLACK);
    DrawText("AR", colX[4], textY, fontSize, BLACK);
    DrawText("MT", colX[5], textY, fontSize, BLACK);
    textY += 20;

    // Dibujar las filas de la tabla para cada enemigo del vector actual
    for (Enemy* enemy : *currentEnemies) {
        // En el futuro, aquí podrías aplicar colores específicos basados en fitness
        Color textColor = enemy->IsMutated() ? GOLD : BLACK; 
        
        DrawText(TextFormat("%.0f", enemy->GetHealth()), colX[0], textY, fontSize, textColor);
        DrawText(TextFormat("%.0f", enemy->GetSpeed()), colX[1], textY, fontSize, textColor);
        DrawText(TextFormat("%d", enemy->GetArrowResistance()), colX[2], textY, fontSize, textColor);
        DrawText(TextFormat("%d", enemy->GetMagicResistance()), colX[3], textY, fontSize, textColor);
        DrawText(TextFormat("%d", enemy->GetArtilleryResistance()), colX[4], textY, fontSize, textColor);
        DrawText(enemy->IsMutated() ? "Y" : "N", colX[5], textY, fontSize, textColor);
        textY += 20; // Espaciado entre filas
    }

    // Dibujar los botones de paginación
    DrawPaginationButtons();
}

void SidePanel::DrawPaginationButtons() {
    // Botón de página anterior
    Rectangle prevButton = {bounds.x + 10, bounds.y + bounds.height - 40, 30, 30};
    DrawRectangleRec(prevButton, DARKGRAY);
    DrawText("<", prevButton.x + 10, prevButton.y + 5, 20, WHITE);

    // Botón de página siguiente
    Rectangle nextButton = {bounds.x + bounds.width - 40, bounds.y + bounds.height - 40, 30, 30};
    DrawRectangleRec(nextButton, DARKGRAY);
    DrawText(">", nextButton.x + 10, nextButton.y + 5, 20, WHITE);
}