#include "raylib.h"
#include "entities/enemies/mercenary/Mercenary.h"

Mercenary::Mercenary(bool alive, Vector2 pos, int speed)
    : isAlive(alive), position(pos), frameSpeed(speed), currentFrame(0), frameCounter(0), texturePath(""), frameCount(8)
{
    if (alive){
        texturePath = "assets/textures/enemies/mercenary/MercenaryMoveSpriteSheet.png";
        frameCount = 9;
    }
    else{
        texturePath = "assets/textures/enemies/mercenary/MercenaryDeathSpriteSheet.png";
        frameCount = 4;
    }
    texture = LoadTexture(texturePath);
    frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height };
}

Mercenary::~Mercenary()
{
    UnloadTexture(texture);
}

void Mercenary::Update()
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


void Mercenary::Draw()
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

void Mercenary::IncreaseSpeed()
{
    if (frameSpeed < maxFrameSpeed)
        frameSpeed++;
}

void Mercenary::DecreaseSpeed()
{
    if (frameSpeed > minFrameSpeed)
        frameSpeed--;
}
