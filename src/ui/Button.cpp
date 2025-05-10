#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string &text, int fontSize, Color textColor,
               const std::string &fontPath, Color normalColor, Color hoverColor, Color pressedColor)
    : bounds({ x, y, width, height }), normalColor(normalColor), hoverColor(hoverColor), pressedColor(pressedColor),
      textElement(text, 0, 0, fontSize, 2.0f, textColor, fontPath) {
    // Centrar el texto dentro del botón
    Vector2 textSize = MeasureTextEx(textElement.GetFont(), text.c_str(), fontSize, 2.0f);
    textElement.SetPosition(bounds.x + (bounds.width - textSize.x) / 2, bounds.y + (bounds.height - textSize.y) / 2);
}

void Button::Draw() {
    Color currentColor = normalColor;
    if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            currentColor = pressedColor;
        } else {
            currentColor = hoverColor;
        }
    }
    DrawRectangleRec(bounds, currentColor);
    textElement.Draw();
}

bool Button::IsClicked() {
    return CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

void Button::SetPosition(float x, float y) {
    bounds.x = x;
    bounds.y = y;
    Vector2 textSize = MeasureTextEx(textElement.GetFont(), textElement.GetText().c_str(), textElement.GetFontSize(), 2.0f);
    textElement.SetPosition(bounds.x + (bounds.width - textSize.x) / 2, bounds.y + (bounds.height - textSize.y) / 2);
}

Vector2 Button::GetPosition() const {
    return { bounds.x, bounds.y };
}

float Button::GetWidth() const {
    return bounds.width;
}

float Button::GetHeight() const {
    return bounds.height;
}