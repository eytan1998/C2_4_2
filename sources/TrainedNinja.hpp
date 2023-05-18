#ifndef TRAINED_NINJA_H
#define TRAINED_NINJA_H

#include "Ninja.hpp"

constexpr int TRAINED_NINJA_SPEED = 12;
constexpr int TRAINED_NINJA_HP = 120;

class TrainedNinja : public Ninja {
public:
    TrainedNinja(string name, Point location) : Ninja(std::move(name), TRAINED_NINJA_HP, location,
                                                      TRAINED_NINJA_SPEED) {};

    string print() override {
        if (isAlive()) {
            return "N" + getName() + ": " + to_string(getHp()) + "/" + to_string(TRAINED_NINJA_HP) + ", Location :" +
                   getLocation().print() + "\n";
        }
        return "N(" + getName() + "): Location :" + getLocation().print() + "\n";
    }
};

#endif