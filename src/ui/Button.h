#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "TextElement.h" // Incluir la clase TextElement
#include <string>

class Button {
private:
    Rectangle bounds;       // Button bounds (position and size)
    Color normalColor;      // Button color when idle
    Color hoverColor;       // Button color when hovered
    Color pressedColor;     // Button color when pressed
    TextElement textElement; // TextElement para manejar el texto del botón

public:
    Button(float x, float y, float width, float height, const std::string &text, int fontSize, Color textColor,
           const std::string &fontPath, Color normalColor = LIGHTGRAY, Color hoverColor = GRAY, Color pressedColor = DARKGRAY);

    void Draw();            // Dibuja el botón
    bool IsClicked();       // Verifica si el botón fue clickeado
};

#endif // BUTTON_H