#ifndef CALC_H
#define CALC_H

#include <vector>

#include "point.h"

using namespace std;

class Calc
{
public:
    Calc() {}

    float calcAccelerationRequired(float initialPosition, float finalPosition, float initialSpeed, float time);
    vector<float> calcAccelerationRequired(Point initialPosition, Point finalPosition, vector<float> initialSpeed, float time);
    float calcCurrentPosition(float initialPosition, float acceleration, float initialSpeed, float time);
    Point calcCurrentPosition(Point initialPosition, vector<float> acceleration, vector<float> initialSpeed, float time);
    float euclideanDistance(int x1, int y1, int x2, int y2);
    float euclideanDistance(Point point1, Point point2);
    vector<float> zerosVector(int numOfDimensions);
};

#endif