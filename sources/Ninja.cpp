
#include "Ninja.hpp"

Ninja::Ninja(string name, int hit_points, Point location, int speed) : Character(std::move(name), hit_points, location),
                                                                       speed(speed) {}

void Ninja::move(Character *enemy) {
    setLocation(Point::moveTowards(getLocation(), enemy->getLocation(), speed));
}

void Ninja::slash(Character *enemy) {
    if (enemy == this) throw std::runtime_error("why are u hitting yourself");
    if (!isAlive()) throw std::runtime_error("(ninja) cant hit while dead");
    if (getLocation().distance(enemy->getLocation()) > 1) return;
    enemy->hit(NINJA_DMG);
}






