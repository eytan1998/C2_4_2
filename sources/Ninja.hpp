
#ifndef NINJA_H
#define NINJA_H

#include "Character.hpp"

constexpr int NINJA_DMG = 40;

class Ninja : public Character {
    int speed;
public:
    Ninja(string name, int hit_points, Point location, int speed);

    virtual void move(Character *enemy);

    void slash(Character *enemy);


};

#endif //NINJA_H
