#include "raylib.h"
#include "DarkElf.h"

DarkElf::DarkElf(bool alive, Vector2 pos, int speed)
    : isAlive(alive), position(pos), frameSpeed(speed), currentFrame(0), frameCounter(0), texturePath(""), frameCount(8)
{
    if (alive){
        texturePath = "../assets/textures/enemies/darkelf/DarkElfMoveSpriteSheet.png";
        frameCount = 8;
    }
    else{
        texturePath = "../assets/textures/enemies/darkelf/DarkElfDeathSpriteSheet.png";
        frameCount = 7;
    }
    texture = LoadTexture(texturePath);
    frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height };
}

DarkElf::~DarkElf()
{
    UnloadTexture(texture);
}

void DarkElf::Update()
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


void DarkElf::Draw()
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

void DarkElf::IncreaseSpeed()
{
    if (frameSpeed < maxFrameSpeed)
        frameSpeed++;
}

void DarkElf::DecreaseSpeed()
{
    if (frameSpeed > minFrameSpeed)
        frameSpeed--;
}

