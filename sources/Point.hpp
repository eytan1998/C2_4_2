#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

using namespace std;
class Point {
    double x, y;
public:
    Point(double a_val,double b_val);
    double distance(Point other) const;
    string print() const;
    static Point moveTowards(Point src,Point dest,double distance);
    friend ostream &operator<<(ostream &output, const Point &point);
    friend bool operator==(const Point &pointA , const Point &pointB);
    friend bool operator!=(const Point &pointA , const Point &pointB);
};


#endif