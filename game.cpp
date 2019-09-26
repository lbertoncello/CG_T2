#include "game.h"

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "calc.h"

using namespace std;

std::chrono::high_resolution_clock::time_point takeOffStartTime;
std::chrono::high_resolution_clock::time_point sizeIncreaseStartTime;
vector<float> takeOffAcceleration;
float sizeIncreaseAcceleration;
float airportRunwayScalarMiddle;
bool beforeAirportRunwayMiddle = true;
Point currentPosition;
Point playerStartPosition;
float originalPlayerRadius;
Calc calc;

vector<float> Game::calcTakeOffAcceleration()
{
    Point initialPosition = airportRunway.getBody().getPoint1();
    //float finalPosition = calc.euclideanDistance(airportRunway.getBody().getPoint1(), airportRunway.getBody().getPoint2());
    Point finalPosition = airportRunway.getBody().getPoint2();
    vector<float> initialSpeed = calc.zerosVector(2);
    float time = TAKEOFF_TIME;

    return calc.calcAccelerationRequired(initialPosition, finalPosition, initialSpeed, time);
}

void Game::takeOff()
{
    playerAirplane.setTakingOff(true);
    originalPlayerRadius = playerAirplane.getBody().getRadius();
    playerStartPosition = airportRunway.getBody().getPoint1();
    takeOffAcceleration = calcTakeOffAcceleration();
    sizeIncreaseAcceleration = calcSizeIncreaseAcceleration();
    currentPosition = airportRunway.getBody().getPoint1();
    takeOffStartTime = std::chrono::high_resolution_clock::now();
}

Point Game::currentTakeOffPosition(float time)
{
    Point initialPosition = airportRunway.getBody().getPoint1();
    vector<float> acceleration = takeOffAcceleration;
    vector<float> initialSpeed = calc.zerosVector(2);

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

float Game::calcSizeIncreaseAcceleration()
{
    float airportRunwayScalarSize = calc.euclideanDistance(airportRunway.getBody().getPoint1(), airportRunway.getBody().getPoint2());
    airportRunwayScalarMiddle = airportRunwayScalarSize / 2.0;
    float airportRunwayScalarAcceleration = calc.calcAccelerationRequired(0.0, airportRunwayScalarSize, 0.0, TAKEOFF_TIME);

    float finalSpeed = calc.calcFinalSpeedRequired(0.0, airportRunwayScalarAcceleration, TAKEOFF_TIME);

    float initialSize = playerAirplane.getBody().getRadius();
    float finalSize = 2 * initialSize;
    float initialSpeed = calc.calcInitialSpeedRequired(finalSpeed, airportRunwayScalarAcceleration, airportRunwayScalarSize/2, airportRunwayScalarSize);
    float time = calc.calcTimeRequired(initialSpeed, finalSpeed, airportRunwayScalarAcceleration);

    return calc.calcAccelerationRequired(initialSize, finalSize, 0, time);
}

float Game::currentRadius(float time)
{
    float initialPosition = originalPlayerRadius;
    float acceleration = sizeIncreaseAcceleration;
    float initialSpeed = 0;

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

void Game::updateTakeOff(float time)
{
    Point currentPositionVariation = this->currentTakeOffPosition(time);
    currentPosition.setX(currentPosition.getX() + currentPositionVariation.getX());
    currentPosition.setY(currentPosition.getY() + currentPositionVariation.getY());

    if (beforeAirportRunwayMiddle == false)
    {
        playerAirplane.getBody().setRadius(currentRadius(time));
    }
}

void Game::drawGame()
{
    glPushMatrix();
    draw.drawFilledCircle(flightArea.getArea());
    glPopMatrix();

    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        glPushMatrix();
        draw.drawFilledCircle(terrestrialEnemies_it->getBody());
        glPopMatrix();
    }

    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        glPushMatrix();
        draw.drawFilledCircle(flightEnemy_it->getBody());
        glPopMatrix();
    }

    glPushMatrix();
    draw.drawLine(airportRunway.getBody());
    glPopMatrix();

    glPushMatrix();
    if (playerAirplane.isTakingOff())
    {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - takeOffStartTime);


        if (time_span.count() >= TAKEOFF_TIME)
        {
            playerAirplane.setTakingOff(false);
            playerAirplane.setFlying(true);
        }
        else
        {
            Point currentPositionVariation = currentTakeOffPosition(time_span.count());
            glTranslatef(currentPositionVariation.getX(), currentPositionVariation.getY(), 0.0);

            currentPosition.setX(playerStartPosition.getX() + currentPositionVariation.getX());
            currentPosition.setY(playerStartPosition.getY() + currentPositionVariation.getY());

            if (beforeAirportRunwayMiddle == false)
            {
                time_span = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - sizeIncreaseStartTime);
                float newRadius = originalPlayerRadius + currentRadius(time_span.count());
                playerAirplane.getBody().setRadius(newRadius);
            }
            else
            {
                float distance = calc.euclideanDistance(currentPosition, airportRunway.getBody().getPoint2());

                if (distance < airportRunwayScalarMiddle)
                {
                    beforeAirportRunwayMiddle = false;
                    sizeIncreaseStartTime = std::chrono::high_resolution_clock::now();
                }
            }
        }
    }
    draw.drawFilledCircle(playerAirplane.getBody());
    glPopMatrix();
}