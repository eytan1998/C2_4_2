
#include "Point.hpp"

Point::Point(double a_val, double b_val) : x(a_val), y(b_val) {}

double Point::distance(Point other) const {
    return std::sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

string Point::print() const {
    return "(" + to_string(x) + "," + to_string(y) + ")";
}

Point Point::moveTowards(Point src, Point dest, double distance) {
    if (distance<0 ) throw std::invalid_argument("cant go backwards");
    double deltaX = dest.x - src.x;
    double deltaY = dest.y - src.y;

    double diff = distance / src.distance(dest);
    if (diff > 1)diff = 1;

    return {src.x + diff * deltaX, src.y + diff * deltaY};
}

ostream &operator<<(ostream &output, const Point &point) {
    output << "(" << point.x << "," << point.y << ")";
    return output;
}

bool operator==(const Point &pointA , const Point &pointB) {
    return (pointA.x == pointB.x && pointA.y == pointB.y);
}

bool operator!=(const Point &pointA, const Point &pointB) {
    return !(pointA==pointB);
}
