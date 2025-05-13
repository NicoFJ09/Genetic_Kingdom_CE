#include "SidePanel.h"
#include "../config/Constants.h"

SidePanel::SidePanel(float x, float y, float width, float height)
    : bounds({x, y, width, height}), currentWave(0), remainingTime(0.0f), currentPageIndex(0) {
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

SidePanel::~SidePanel() {
    // Descargar todas las texturas almacenadas en el mapa
    for (auto& pair : enemyTextures) {
        UnloadTexture(pair.second);
    }
    enemyTextures.clear();
}

void SidePanel::UpdateWaveInfo(int wave, float time) {
    currentWave = wave;
    remainingTime = time;
}

void SidePanel::SetActiveEnemies(const std::vector<Enemy*>& enemies) {
    activeEnemies = enemies;
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
    float textX = bounds.x + 10;
    float textY = bounds.y + 10;

    DrawText(TextFormat("Wave: %d", currentWave), textX, textY, fontSize, WHITE);
    textY += 30;
    DrawText(TextFormat("Time Remaining: %.2f", remainingTime), textX, textY, fontSize, WHITE);
    textY += 40;

    // Obtener el tipo de enemigo actual
    const std::string& currentType = enemyTypes[currentPageIndex];

    // Dibujar el título del tipo de enemigo (centrado en X)
    int typeTextWidth = MeasureText(currentType.c_str(), fontSize);
    float typeTextX = bounds.x + (bounds.width - typeTextWidth) / 2;
    DrawText(currentType.c_str(), typeTextX, textY, fontSize, BLACK);
    textY += 30;

    // Dibujar la generación del enemigo (centrado en X)
    int generation = Enemy::GetCurrentGeneration(); // Obtener la generación actual
    std::string generationText = TextFormat("Generation: %d", generation);
    int generationTextWidth = MeasureText(generationText.c_str(), fontSize);
    float generationTextX = bounds.x + (bounds.width - generationTextWidth) / 2;
    DrawText(generationText.c_str(), generationTextX, textY, fontSize, DARKGRAY);
    textY += 30;

    // Contar mutaciones para el tipo actual
    int mutationCount = 0;
    for (Enemy* enemy : activeEnemies) {
        if (enemy->GetEnemyType() == currentType && enemy->IsMutated()) {
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
    DrawText("V", colX[0], textY, fontSize, BLACK);
    DrawText("S", colX[1], textY, fontSize, BLACK);
    DrawText("FR", colX[2], textY, fontSize, BLACK);
    DrawText("MR", colX[3], textY, fontSize, BLACK);
    DrawText("AR", colX[4], textY, fontSize, BLACK);
    DrawText("M", colX[5], textY, fontSize, BLACK);
    textY += 20;

    // Dibujar las filas de la tabla para cada enemigo del tipo actual
    for (Enemy* enemy : activeEnemies) {
        if (enemy->GetEnemyType() == currentType) {
            DrawText(TextFormat("%d", enemy->GetHealth()), colX[0], textY, fontSize, BLACK);
            DrawText(TextFormat("%d", enemy->GetSpeed()), colX[1], textY, fontSize, BLACK);
            DrawText(TextFormat("%d", enemy->GetArrowResistance()), colX[2], textY, fontSize, BLACK);
            DrawText(TextFormat("%d", enemy->GetMagicResistance()), colX[3], textY, fontSize, BLACK);
            DrawText(TextFormat("%d", enemy->GetArtilleryResistance()), colX[4], textY, fontSize, BLACK);
            DrawText(enemy->IsMutated() ? "Y" : "N", colX[5], textY, fontSize, BLACK);
            textY += 20; // Espaciado entre filas
        }
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