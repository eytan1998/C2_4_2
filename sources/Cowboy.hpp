
#ifndef COWBOY_H
#define COWBOY_H

#include "Character.hpp"
#include <utility>
#include <string>

constexpr int COWBOY_DMG = 10;
constexpr int COWBOY_BULLETS = 6;
constexpr int COWBOY_HP = 110;

class Cowboy : public Character {
    int bullet;
public:
    Cowboy(string name, Point location);

    void shoot(Character *enemy);

    bool hasboolets() const;

    void reload();

    string print() override;
};


#endif //COWBOY_H
