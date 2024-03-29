#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "color.h"

class Line
{
    int id;
    Point point1;
    Point point2;
    Color color;

public:
    Line() {}

    Line(Point point1, Point point2)
    {
        this->point1 = point1;
        this->point2 = point2;
    }

    Line(int id, Point point1, Point point2)
    {
        this->id = id;
        this->point1 = point1;
        this->point2 = point2;
    }

    int getId()
    {
        return id;
    }

    Point& getPoint1()
    {
        return point1;
    }

    Point& getPoint2()
    {
        return point2;
    }

    float getPoint1_x()
    {
        return point1.getX();
    }

    float getPoint1_y()
    {
        return point1.getY();
    }

    float getPoint2_x()
    {
        return point2.getX();
    }

    float getPoint2_y()
    {
        return point2.getY();
    }

    Color& getColor()
    {
        return color;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void setPoint1(Point point)
    {
        this->point1.update(point);
    }

    void setPoint2(Point point)
    {
        this->point2.update(point);
    }

    void setPoint1_x(float x)
    {
        this->point1.setX(x);
    }

    void setPoint1_y(float y)
    {
        this->point1.setY(y);
    }

    void setPoint2_x(float x)
    {
        this->point2.setX(x);
    }

    void setPoint2_y(float y)
    {
        this->point2.setY(y);
    }

    void setColor(Color color)
    {
        this->color = color;
    }
};

#endif