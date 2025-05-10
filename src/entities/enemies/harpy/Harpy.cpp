#include "raylib.h"
#include "Harpy.h"

Harpy::Harpy(bool alive, Vector2 pos, int speed)
    : isAlive(alive), position(pos), frameSpeed(speed), currentFrame(0), frameCounter(0), texturePath(""), frameCount(8)
{
    if (alive){
        texturePath = "../assets/textures/enemies/harpy/HarpyMoveSpriteSheet.png";
        frameCount = 24;
    }
    else{
        texturePath = "../assets/textures/enemies/harpy/HarpyDeathSpriteSheet.png";
        frameCount = 7;
    }
    texture = LoadTexture(texturePath);
    frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height };
}

Harpy::~Harpy()
{
    UnloadTexture(texture);
}

void Harpy::Update()
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


void Harpy::Draw()
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

void Harpy::IncreaseSpeed()
{
    if (frameSpeed < maxFrameSpeed)
        frameSpeed++;
}

void Harpy::DecreaseSpeed()
{
    if (frameSpeed > minFrameSpeed)
        frameSpeed--;
}
