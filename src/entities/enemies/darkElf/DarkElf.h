#ifndef DARKELF_H
#define DARKELF_H

#include "../Enemy.h"

class DarkElf : public Enemy {
public:
    DarkElf(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation = 1, int mutationChance = 5);
    ~DarkElf() = default; // Destructor predeterminado
    double getRandomHealth();
    double getRandomSpeed();
    double getRandomResist();
};

#endif // DARKELF_H