#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "Screen.h"
#include "../ui/TextElement.h"
#include "../ui/Button.h"
#include "../entities/enemies/ogre/Ogre.h"
#include "../entities/enemies/harpy/Harpy.h"
#include "ScreenManager.h"

class StartScreen : public Screen {
private:
    TextElement title; // Título centrado
    Button startButton; // Botón de inicio
    int screenWidth;
    int screenHeight;
    ScreenManager* screenManager; // Puntero al ScreenManager

    // Entidades
    Ogre ogre;
    Harpy harpy;

public:
    StartScreen(int screenWidth, int screenHeight, ScreenManager* screenManager);
    void Update() override; // Actualiza la lógica de la pantalla
    void Draw() override;   // Dibuja la pantalla
};

#endif // START_SCREEN_H