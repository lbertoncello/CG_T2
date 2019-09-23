#ifndef TERRESTRIAL_ENEMY_H
#define TERRESTRIAL_ENEMY_H

#include "enemy.h"

class TerrestrialEnemy : public Enemy
{

public:
    TerrestrialEnemy() {}

    TerrestrialEnemy(Circle body) : Enemy(body) {}
};

#endif