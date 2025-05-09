#include "TextElement.h"

TextElement::TextElement(const std::string &text, float x, float y, int fontSize, float spacing, Color color, const std::string &fontPath)
    : text(text), position({x, y}), fontSize(fontSize), spacing(spacing), color(color) {
        font = LoadFont(fontPath.c_str());
        if (font.texture.id == 0) {
            TraceLog(LOG_ERROR, "Failed to load font: %s", fontPath.c_str());
        }
}

void TextElement::Draw() {
    if (font.texture.id != 0) {
        DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
    } else {
        TraceLog(LOG_ERROR, "Font not loaded, cannot draw text.");
    }
}

void TextElement::SetText(const std::string &newText) {
    text = newText;
}

void TextElement::SetPosition(float x, float y) {
    position = {x, y};
}

void TextElement::Center(int screenWidth, int screenHeight) {
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    position.x = (screenWidth - textSize.x) / 2;
    position.y = (screenHeight - textSize.y) / 2;
}

Font TextElement::GetFont() const {
    return font;
}

TextElement::~TextElement() {
    UnloadFont(font);
}