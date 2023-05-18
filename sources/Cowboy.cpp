
#include "Cowboy.hpp"

Cowboy::Cowboy(string name, Point location) : Character(std::move(name), COWBOY_HP, location), bullet(COWBOY_BULLETS) {}

void Cowboy::shoot(Character *enemy) {
    if(enemy == this) throw std::runtime_error("why are u hitting yourself");
    //if dead / out of bullet
    if(!isAlive()) throw std::runtime_error("cant hit  dead-body or while dead");
    if (!hasboolets()) return;
    enemy->hit(COWBOY_DMG);
    bullet--;
}

bool Cowboy::hasboolets() const { return bullet > 0; }

void Cowboy::reload() {
    if(!isAlive()) throw std::runtime_error("dead man walking");
    bullet = COWBOY_BULLETS;
}


string Cowboy::print() {
    if(isAlive()){
        return "C"+getName()+": "+ to_string(getHp())+"/"+ to_string(COWBOY_HP)+", Location :"+getLocation().print()+"\n";
    }
    return "C("+getName()+"): Location :"+getLocation().print()+"\n";

}
