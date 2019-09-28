#include "playerAirplane.h"

void PlayerAirplane::draw() {
    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);
}