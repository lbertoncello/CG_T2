#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "playerAirplane.h"
#include "airportRunway.h"
#include "flightArea.h"
#include "flightEnemy.h"
#include "terrestrialEnemy.h"

#define TAKEOFF_TIME 4.0

using namespace std::chrono;
using namespace std;

//using namespace std::chrono;

class Game
{
    Draw draw;
    FlightArea flightArea;
    PlayerAirplane playerAirplane;
    AirportRunway airportRunway;
    vector<FlightEnemy> flightEnemies;
    vector<TerrestrialEnemy> terrestrialEnemies;

    void updateTakeOff(high_resolution_clock::time_point currentTime, float takeOffTimeElapsed);

public:
    Game() {}

    AirportRunway& getAirportRunway() {
        return airportRunway;
    }

    void setFlightArea(FlightArea flightArea) {
        this->flightArea = flightArea;
    }

    void setPlayerAirplane(PlayerAirplane playerAirplane) {
        this->playerAirplane = playerAirplane;
    }

    void setAirportRunway(AirportRunway airportRunway) {
        this->airportRunway = airportRunway;
    }

    void addFlightEnemy(FlightEnemy flightEnemy)
    {
        flightEnemies.push_back(flightEnemy);
    }

    void addTerrestrialEnemy(TerrestrialEnemy terrestrialEnemy)
    {
        terrestrialEnemies.push_back(terrestrialEnemy);
    }

    bool isPlayerFlying() {
        return playerAirplane.isFlying();
    }

    bool isPlayerTakingOff() {
        return playerAirplane.isTakingOff();
    }

    void playerTakeOff() {
        playerAirplane.setFlying(true);
    }

    vector<float> calcTakeOffAcceleration();
    Point currentTakeOffPosition(float time);
    float calcSizeIncreaseAcceleration();
    float currentRadius(float time);
    void takeOff();
    void drawGame();
};

#endif