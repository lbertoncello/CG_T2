#ifndef AIRPORT_RUNWAY_H
#define AIRPORT_RUNWAY_H

#include "line.h"

class AirportRunway
{
    Line body;
    float scalarMiddle;

public:
    AirportRunway() {}

    AirportRunway(Line body)
    {
        this->body = body;
    }

    Line &getBody()
    {
        return body;
    }

    float getScalarMiddle()
    {
        return scalarMiddle;
    }

    void setBody(Line body)
    {
        this->body = body;
    }

    void setScalarMiddle(float scalarMiddle)
    {
        this->scalarMiddle = scalarMiddle;
    }
};

#endif