#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "Screen.h"

class ScreenManager {
private:
    Screen* currentScreen; // Pantalla actual

public:
    ScreenManager();
    ~ScreenManager();

    void SwitchToScreen(Screen* newScreen); // Cambiar a una pantalla específica
    void Update();                          // Actualizar la pantalla actual
    void Draw();                            // Dibujar la pantalla actual
};

#endif // SCREEN_MANAGER_H