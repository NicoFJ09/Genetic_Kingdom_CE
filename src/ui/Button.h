#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "TextElement.h"
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
    void SetPosition(float x, float y);       // Cambia la posición del botón
    Vector2 GetPosition() const;             // Obtiene la posición del botón
    float GetWidth() const;                  // Obtiene el ancho del botón
    float GetHeight() const;                 // Obtiene el alto del botón
};

#endif // BUTTON_H