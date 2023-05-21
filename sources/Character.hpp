

#ifndef CHARACTER_H
#define CHARACTER_H


#include "Point.hpp"

class Character {
    Point location;
    string name;
    bool inTeam;
    int hp;
public:
    Character(string name, int hit_points, Point location) : name(std::move(name)), hp(hit_points),
                                                             location(location), inTeam(false) {
        if (hp <= 0) {
            throw invalid_argument("cant create dead character");
        }
    }
    //for delete in team
    virtual ~Character() = default;

    //to get hp in sons
    int getHp() const {return hp;}

    bool isAlive() const { return hp > 0; }

    bool isBusy() const { return inTeam; }

    //so won't join other team
    void joinTeam() { inTeam = true; }

    double distance(Character *other) {
        return location.distance(other->location);
    }

    void hit(int dmg) {
        if (dmg <= 0) {throw std::invalid_argument("cant dmg negative number");}
        if (!isAlive()) {throw std::runtime_error("cant dmg dead-body");}

        //not need to kill him more
        if (dmg > hp){ hp = 0;}
        else{ hp -= dmg;}

    }

    string getName() {
        return name;
    }

    Point getLocation() {
        return location;
    }

    void setLocation(Point newPoint) {
        location = newPoint;
    }
    //dont print character
    virtual string print() = 0;
};


#endif //CHARACTER_H
