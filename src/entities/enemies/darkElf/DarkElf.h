#ifndef DarkElf_H
#define DarkElf_H

#include "raylib.h"

class DarkElf {
public:
    DarkElf(bool alive, Vector2 position, int frameSpeed);
    ~DarkElf();

    void Update();
    void Draw();

    //Increase or decrease speed depending on speed property from DarkElf instance
    void IncreaseSpeed();
    void DecreaseSpeed();

private:
    Texture2D texture;
    Vector2 position;
    Rectangle frameRec;
    bool isAlive;
    const char *texturePath;
    int currentFrame;
    int frameCount;
    int frameSpeed;
    int frameCounter;

    const int maxFrameSpeed = 15;
    const int minFrameSpeed = 1;
};

#endif
