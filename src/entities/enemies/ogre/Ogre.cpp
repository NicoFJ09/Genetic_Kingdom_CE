#include "raylib.h"
#include "Ogre.h"

Ogre::Ogre(bool alive, Vector2 position, int speed)
    : isAlive(alive), position(position), frameSpeed(speed), currentFrame(0), frameCounter(0), texturePath(""), frameCount(8)
{
    if (alive){
        texturePath = "../assets/textures/enemies/ogre/OgreMoveSpriteSheet.png";
        frameCount = 8;
    }
    else{
        texturePath = "../assets/textures/enemies/ogre/OgreDeathSpriteSheet.png";
        frameCount = 4;
    }
    texture = LoadTexture(texturePath);
    frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height };
}

Ogre::~Ogre()
{
    UnloadTexture(texture);
}

void Ogre::Update()
{
    frameCounter++;

        if (frameCounter >= (60 / frameSpeed))
        {
            frameCounter = 0;
    
            if (isAlive)
            {
                currentFrame = (currentFrame + 1) % frameCount;
            }
            else
            {
                if (currentFrame < frameCount - 1)
                {
                    currentFrame++;
                }
            }
    
            frameRec.x = (float)currentFrame * frameRec.width;
    }
}


void Ogre::Draw()
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

void Ogre::IncreaseSpeed()
{
    if (frameSpeed < maxFrameSpeed)
        frameSpeed++;
}

void Ogre::DecreaseSpeed()
{
    if (frameSpeed > minFrameSpeed)
        frameSpeed--;
}
