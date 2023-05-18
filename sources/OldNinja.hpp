
#ifndef OLD_NINJA_H
#define OLD_NINJA_H

#include "Ninja.hpp"

constexpr int OLD_NINJA_SPEED = 8;
constexpr int OLD_NINJA_HP = 150;

class OldNinja : public Ninja {

public:
    OldNinja(string name, Point location) : Ninja(std::move(name), OLD_NINJA_HP, location, OLD_NINJA_SPEED) {};

    string print() override {
        if (isAlive()) {
            return "N" + getName() + ": " + to_string(getHp()) + "/" + to_string(OLD_NINJA_HP) + ", Location :" +
                   getLocation().print() + "\n";
        }
        return "N(" + getName() + "): Location :" + getLocation().print() + "\n";
    }
};

#endif