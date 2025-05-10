#ifndef DARKELF_H
#define DARKELF_H

#include "../Enemy.h"

class DarkElf : public Enemy {
public:
    DarkElf(bool alive, Vector2 position, int frameSpeed);
    ~DarkElf() = default; // Destructor predeterminado
};

#endif // DARKELF_H