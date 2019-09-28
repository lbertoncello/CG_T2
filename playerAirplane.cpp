#include "playerAirplane.h"

void PlayerAirplane::draw() {
    //cout << "radius: " << this->getBody().getRadius() << endl;
    
    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);
}