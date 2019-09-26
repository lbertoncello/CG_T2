#ifndef AIRPORT_RUNWAY_H
#define AIRPORT_RUNWAY_H

#include "line.h"

class AirportRunway
{
    Line body;
public:
    AirportRunway() {}

    AirportRunway(Line body) {
        this->body = body;
    }

    Line& getBody() {
        return body;
    }

    void setBody(Line body) {
        this->body = body;
    }
};

#endif