#ifndef FLIGHT_AREA_H
#define FLIGHT_AREA_H

#include "circle.h"

class FlightArea {
    Circle area;

    public:

    FlightArea() {}

    FlightArea(Circle circle) {
        this->area = circle;
    }

    Circle getArea() {
        return area;
    }

    void setArea(Circle area) {
        this->area = area;
    }
};

#endif