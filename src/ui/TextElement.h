#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include "raylib.h"
#include <string>

class TextElement {
private:
    Vector2 position;       // Posición del texto
    std::string text;       // Contenido del texto
    Font font;              // Fuente personalizada
    int fontSize;           // Tamaño de la fuente
    float spacing;          // Espaciado entre caracteres
    Color color;            // Color del texto

public:
    TextElement(const std::string &text, float x, float y, int fontSize, float spacing, Color color, const std::string &fontPath);

    void Draw();            // Dibuja el texto en pantalla
    void SetText(const std::string &newText); // Cambia el texto
    void SetPosition(float x, float y);       // Cambia la posición
    void Center(int screenWidth, int screenHeight); // Centra el texto en la pantalla
    Font GetFont() const;   // Devuelve la fuente utilizada
    ~TextElement();
};

#endif // TEXT_ELEMENT_H