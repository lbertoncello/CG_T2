#ifndef GAME_H
#define GAME_H

#include "draw.h"
#include "playerAirplane.h"
#include "airportRunway.h"
#include "flightArea.h"
#include "flightEnemy.h"
#include "terrestrialEnemy.h"

#define TAKEOFF_TIME 4.0

class Game
{
    Draw draw;
    FlightArea flightArea;
    PlayerAirplane playerAirplane;
    AirportRunway airportRunway;
    vector<FlightEnemy> flightEnemies;
    vector<TerrestrialEnemy> terrestrialEnemies;

public:
    Game() {}

    AirportRunway getAirportRunway() {
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

    bool playerIsFlying() {
        return playerAirplane.isFlying();
    }

    void playerTakeOff() {
        playerAirplane.setFlying(true);
    }

    vector<float> takeOffAcceleration();
    Point currentTakeOffPosition(float time);
    void takeOff();
    void updateTakeOff(float time);
    void drawGame();
};

#endif