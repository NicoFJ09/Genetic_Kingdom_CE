#ifndef BRIDGETILE_H
#define BRIDGETILE_H

#include "Tile.h"
#include "../entities/enemies/Enemy.h"
#include <vector>

class BridgeTile : public Tile {
private:
    Texture2D texture;
    bool CheckEnemyCollision(const std::vector<Enemy*>& enemies) const;

public:
    BridgeTile(Vector2 position, Texture2D texture);
    void Draw() const override;
    
    // Método para verificar colisión con enemigos
    bool IsUnderAttack(const std::vector<Enemy*>& enemies) const;
};

#endif // BRIDGETILE_H