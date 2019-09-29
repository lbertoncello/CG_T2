#ifndef PLAYER_AIRPLANE_H
#define PLAYER_AIRPLANE_H

#include "circle.h"
#include "draw.h"
#include "calc.h"

#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

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
    vector<float> speed;
    float speedMultiplier;
    Calc calc;

    void speedInit()
    {
        speed.push_back(0);
        speed.push_back(0);
    }

public:
    PlayerAirplane()
    {
        speedInit();
    }

    PlayerAirplane(Circle body)
    {
        this->body = body;
        initialRadius = body.getRadius();
        initialRadiusInitialized = true;
        speedInit();
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

    vector<float> &getSpeed()
    {
        return speed;
    }

    float getSpeedMultiplier()
    {
        return speedMultiplier;
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

    void setSpeed(vector<float> speed)
    {
        float speedNorm = calc.norm(speed);

        this->speed[0] = speedNorm / 2 * this->speedMultiplier;
        this->speed[1] = speedNorm / 2 * this->speedMultiplier;
    }

    void setSpeedMultiplier(float speedMultiplier)
    {
        this->speedMultiplier = speedMultiplier;
    }

    void draw();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool checkIntersection(Circle circle, int moveDirection);
    bool isInside(Circle circle, int moveDirection);
};

#endif