#ifndef FLIGHT_ENEMY_H
#define FLIGHT_ENEMY_H

#include "enemy.h"

class FlightEnemy : public Enemy
{

public:
    FlightEnemy() {}

    FlightEnemy(Circle body) : Enemy(body) {}
};

#endif