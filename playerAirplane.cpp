#include "playerAirplane.h"

#include "draw.h"

Draw drawer;

void PlayerAirplane::draw() {
    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);
}