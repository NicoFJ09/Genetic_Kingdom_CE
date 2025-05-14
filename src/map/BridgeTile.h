#ifndef BRIDGETILE_H
#define BRIDGETILE_H

#include "Tile.h"

class BridgeTile : public Tile {
private:
    Texture2D texture;

public:
    BridgeTile(Vector2 position, Texture2D texture);
    void Draw() const override;
};

#endif // BRIDGETILE_H