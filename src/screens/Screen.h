#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
    virtual void Update() = 0; // Método para actualizar la lógica de la pantalla
    virtual void Draw() = 0;   // Método para dibujar la pantalla
    virtual ~Screen() = default;
};

#endif // SCREEN_H