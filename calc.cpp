#include "calc.h"

#include <cmath>

using namespace std;

//S=So+Vot+at2/2

float Calc::euclideanDistance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

float Calc::euclideanDistance(Point point1, Point point2)
{
    return euclideanDistance(point1.getX(), point1.getY(), point2.getX(), point2.getY());
}

float Calc::calcAccelerationRequired(float initialPosition, float finalPosition, float initialSpeed, float time)
{
    return 2 * (finalPosition - initialPosition - initialSpeed * time) / (time * time);
}

float Calc::calcCurrentPosition(float initialPosition, float acceleration, float initialSpeed, float time)
{
    return (initialPosition + initialSpeed * time + (acceleration * pow(time, 2)) / 2);
}

vector<float> Calc::calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<float> initialSpeed, float time)
{
    vector<float> acceleration;

    float acceleration_x = calcAccelerationRequired(initialPosition.getX(), finalPosition.getX(), initialSpeed[0], time);
    float acceleration_y = calcAccelerationRequired(initialPosition.getY(), finalPosition.getY(), initialSpeed[1], time);

    acceleration.push_back(acceleration_x);
    acceleration.push_back(acceleration_y);

    return acceleration;
}

Point Calc::calcCurrentPosition(Point initialPosition, vector<float> acceleration, vector<float> initialSpeed, float time)
{
    Point currentPosition;

    float currentPosition_x = calcCurrentPosition(initialPosition.getX(), acceleration[0], initialSpeed[0], time);
    float currentPosition_y = calcCurrentPosition(initialPosition.getY(), acceleration[1], initialSpeed[1], time);

<<<<<<< HEAD
    currentPosition.setX(currentPosition_x);
    currentPosition.setY(currentPosition_y);
=======
    acceleration.push_back(currentPosition_y);
    acceleration.push_back(currentPosition_y);
>>>>>>> b961bf5396425515e6d34e92964132f0c446c4d1

    return currentPosition;
}

vector<float> Calc::zerosVector(int numOfDimensions) {
    vector<float> zeros;

    for(int i = 0; i < numOfDimensions; i++) {
        zeros.push_back(0);
    }

    return zeros;
}