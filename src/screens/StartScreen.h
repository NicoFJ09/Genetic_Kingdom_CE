#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Screen.h"
#include "../ui/TextElement.h"
#include "../ui/Button.h"
#include "../entities/enemies/Enemy.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "../entities/enemies/mercenary/Mercenary.h"
#include "ScreenManager.h"
#include <vector> // Para manejar enemigos localmente

class StartScreen : public Screen {
private:
    TextElement title; // Título centrado
    Button startButton; // Botón de inicio
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Puntero al ScreenManager

    std::vector<Enemy*> enemies; // Contenedor local para manejar enemigos

public:
    StartScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    ~StartScreen();
    void Update() override; // Actualiza la lógica de la pantalla
    void Draw() override;   // Dibuja la pantalla
};

#endif