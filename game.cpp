#include "game.h"

#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

#include "calc.h"

using namespace std;

std::chrono::high_resolution_clock::time_point takeOffStartTime;
Calc calc;

vector<float> Game::takeOffAcceleration()
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
    cout << "Taking off" << endl;
    playerAirplane.setTakingOff(true);
    takeOffStartTime = std::chrono::high_resolution_clock::now();
}

Point Game::currentTakeOffPosition(float time) {
    Point initialPosition = airportRunway.getBody().getPoint1();
    vector<float> acceleration = this->takeOffAcceleration();
    vector<float> initialSpeed = calc.zerosVector(2);

    cout << "Aceleração: (" << acceleration[0] << ", " << acceleration[1] << ")" << endl;

    return calc.calcCurrentPosition(initialPosition, acceleration, initialSpeed, time);
}

void Game::updateTakeOff(float time) {
    Point currentPosition = this->currentTakeOffPosition(time);

    cout << "Current position: (" << currentPosition.getX() << ", " << currentPosition.getY() << ")" << endl;
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

    if(playerAirplane.isTakingOff()) {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - takeOffStartTime);

        if(time_span.count() >= TAKEOFF_TIME) {
            playerAirplane.setTakingOff(false);
            playerAirplane.setFlying(true);
        }

        updateTakeOff(time_span.count());
    }

    glPushMatrix();
        draw.drawFilledCircle(playerAirplane.getBody());
    glPopMatrix();
}