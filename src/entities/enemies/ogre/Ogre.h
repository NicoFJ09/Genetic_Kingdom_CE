#ifndef OGRE_H
#define OGRE_H

#include "raylib.h"

class Ogre {
public:
    Ogre(bool alive, Vector2 position, int frameSpeed);
    ~Ogre();

    void Update();
    void Draw();

    //Increase or decrease speed depending on speed property from Ogre instance
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
