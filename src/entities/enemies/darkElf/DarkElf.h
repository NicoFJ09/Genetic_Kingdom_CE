#ifndef DARKELF_H
#define DARKELF_H

#include "../Enemy.h"

class DarkElf : public Enemy {
public:
    DarkElf(bool alive, bool mutated, Vector2 position, int frameSpeed, int generation);
    ~DarkElf() = default; // Destructor predeterminado
};

#endif // DARKELF_H