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

bool PlayerAirplane::checkIntersection(Circle circle, int moveDirection)
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    switch (moveDirection)
    {
    case MOVE_UP:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() - speed[1]);
        break;
    case MOVE_DOWN:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() + speed[1]);
        break;
    case MOVE_LEFT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() - speed[0]);
        break;
    case MOVE_RIGHT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() + speed[0]);
        break;
    }

    return adjustedBody.checkIntersection(circle, this->drawer.getNumSegments());
}

bool PlayerAirplane::isInside(Circle circle, int moveDirection)
{
    Circle adjustedBody = this->body;
    adjustedBody.setCenter_x(adjustedBody.getCenter_x() + this->dX);
    adjustedBody.setCenter_y(adjustedBody.getCenter_y() + this->dY);

    switch (moveDirection)
    {
    case MOVE_UP:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() - speed[1]);
        break;
    case MOVE_DOWN:
        adjustedBody.setCenter_y(adjustedBody.getCenter_y() + speed[1]);
        break;
    case MOVE_LEFT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() - speed[0]);
        break;
    case MOVE_RIGHT:
        adjustedBody.setCenter_x(adjustedBody.getCenter_x() + speed[0]);
        break;
    }

    return circle.isInside(adjustedBody, this->drawer.getNumSegments());
}