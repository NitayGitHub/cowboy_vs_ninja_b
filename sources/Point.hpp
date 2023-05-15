#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel
{
    class Point
    {
    private:
        double x, y;

    public:
        Point(double x, double y);
        double distance(const Point &other) const;
        void print() const;
        static Point moveTowards(const Point &source, const Point &dest, double dist);

        // getters and setters
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
        string toString() const;
        
        //
        bool operator==(const Point &other) const;
    };
}
#endif