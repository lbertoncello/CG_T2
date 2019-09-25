#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"

class PlayerAirplane
{
    Circle body;
    bool flying = false;
    bool takingOff = false;

public:
    PlayerAirplane() {}

    PlayerAirplane(Circle body)
    {
        this->body = body;
    }

    Circle getBody()
    {
        return body;
    }

    bool isFlying()
    {
        return flying;
    }

    bool isTakingOff()
    {
        return takingOff;
    }

    void setBody(Circle body)
    {
        this->body = body;
    }

    void setFlying(bool flying)
    {
        this->flying = flying;
    }

    void setTakingOff(bool takingOff) {
        this->takingOff = takingOff;
    }
};

#endif