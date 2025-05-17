#ifndef DARKELF_H
#define DARKELF_H

#include "../Enemy.h"

class DarkElf : public Enemy {
public:
    DarkElf(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation);
    ~DarkElf() = default; // Destructor predeterminado
    double getRandomHealth();
    double getRandomSpeed();
    double getRandomResist();
    DarkElf* Clone() const override { return new DarkElf(*this); }
};

#endif // DARKELF_H