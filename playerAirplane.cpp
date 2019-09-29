#include "playerAirplane.h"

void PlayerAirplane::draw()
{
    //cout << "radius: " << this->getBody().getRadius() << endl;

    glTranslatef(dX, dY, 0.0);
    drawer.drawFilledCircle(this->body);
}

void PlayerAirplane::moveUp()
{
    dY -= speed[1];
}

void PlayerAirplane::moveDown()
{
    dY += speed[1];
}

void PlayerAirplane::moveLeft()
{
    dX -= speed[0];    
}

void PlayerAirplane::moveRight()
{
    dX += speed[0];    
}