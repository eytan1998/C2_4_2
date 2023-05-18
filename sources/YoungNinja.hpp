#ifndef YOUNG_NINJA_H
#define YOUNG_NINJA_H
#include "Ninja.hpp"

constexpr int YOUNG_NINJA_SPEED = 14;
constexpr int YOUNG_NINJA_HP = 100;


class YoungNinja : public Ninja {
public:
    YoungNinja(string name, Point location) : Ninja(std::move(name), YOUNG_NINJA_HP, location, YOUNG_NINJA_SPEED) {};
    string print() override {
        if (isAlive()) {
            return "N" + getName() + ": " + to_string(getHp()) + "/" + to_string(YOUNG_NINJA_HP) + ", Location :" +
                   getLocation().print() + "\n";
        }
        return "N(" + getName() + "): Location :" + getLocation().print() + "\n";
    }
};

#endif