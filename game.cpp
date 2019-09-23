#include "game.h"

void Game::drawGame()
{
    draw.drawFilledCircle(flightArea.getArea());

    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for(terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++) {
        draw.drawFilledCircle(terrestrialEnemies_it->getBody());
    }

    vector<FlightEnemy>::iterator flightEnemy_it;
    for(flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++) {
        draw.drawFilledCircle(flightEnemy_it->getBody());
    }

    draw.drawLine(airportRunway.getBody());
    draw.drawFilledCircle(playerAirplane.getBody());
}