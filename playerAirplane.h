#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"

class PlayerAirplane
{
    Circle body;

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

    void setBody(Circle body)
    {
        this->body = body;
    }
};

#endif