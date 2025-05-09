#include "raylib.h"
#include "entities/enemies/ogre/Ogre.h"

Ogre::Ogre(bool alive, Vector2 pos, int speed)
    : position(pos), frameSpeed(speed), currentFrame(0), frameCounter(0), texturePath(""), frameCount(8)
{
    if (alive){
        texturePath = "assets/textures/enemies/ogre/OgreMoveSpriteSheet.png";
        frameCount = 8;
    }
    else{
        texturePath = "assets/textures/enemies/ogre/OgreDeathSpriteSheet.png";
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
    
            if (alive)
            {
                currentFrame = (currentFrame + 1) % frameCount;
            }
            else
            {
                if (currentFrame < frameCount - 1)
                {
                    currentFrame++;
                }
                else{
                    currentFrame = frameCount+3;
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
