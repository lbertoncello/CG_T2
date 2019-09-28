#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"
#include "draw.h"

class PlayerAirplane
{
    Circle body;
    Point currentPosition;
    Point startPosition;
    float initialRadius;
    float dX = 0; //variação em X
    float dY = 0; //variação em Y
    bool flying = false;
    bool takingOff = false;
    bool startPositionInitialized = false;
    bool initialRadiusInitialized = false;
    Draw drawer;

public:
    PlayerAirplane() {}

    PlayerAirplane(Circle body)
    {
        this->body = body;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
    }

    Circle &getBody()
    {
        return body;
    }

    Point getCurrentPosition()
    {
        return currentPosition;
    }

    Point getStartPosition()
    {
        return startPosition;
    }

    float getInitialRadius()
    {
        return initialRadius;
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

        if (initialRadiusInitialized == false)
        {
            initialRadius = body.getRadius();
            initialRadiusInitialized = true;
        }
    }

    void setCurrentPosition(Point currentPosition)
    {
        if (startPositionInitialized == false)
        {
            startPosition.setX(currentPosition.getX());
            startPosition.setY(currentPosition.getY());
            startPositionInitialized = true;
        }

        dX = currentPosition.getX() - this->startPosition.getX();
        dY = currentPosition.getY() - this->startPosition.getY();

        this->currentPosition = currentPosition;
    }

    void setFlying(bool flying)
    {
        this->flying = flying;
    }

    void setTakingOff(bool takingOff)
    {
        this->takingOff = takingOff;
    }

    void draw();
};

#endif