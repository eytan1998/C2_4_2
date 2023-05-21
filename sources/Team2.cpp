
#include "Team2.hpp"

Team2::Team2(Character *leader) : Team(leader) {}

void Team2::attack(Team *enemy) {
    if (enemy == nullptr) throw std::invalid_argument("null");
    if (enemy->stillAlive() <= 0) throw std::runtime_error("Cant fight the dead");

    //set new leader if needed
    if (!getLeader()->isAlive()) {
        Character* closest = closestToLeader(getLeader());//won't send leader because is dead
        if (closest == nullptr) return; // team dead
        setLeader(closest);
    }

    Character* target;
    for (auto &i: getTeam()) {
        if (i == nullptr) break;
        if (!i->isAlive()) continue;
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            //change target if needed
            target = enemy->closestToLeader(getLeader());
            if (target == nullptr)return;

            auto *cowboy = dynamic_cast<Cowboy *>(i);
            if (cowboy->hasboolets()) {
                cowboy->shoot(target);
            } else {
                cowboy->reload();
            }
        }
        if (dynamic_cast<Ninja *>(i) != nullptr) {
            //change target if needed
            target = enemy->closestToLeader(getLeader());
            if (target == nullptr)return;

            auto *ninja = dynamic_cast<Ninja *>(i);
            if (target->getLocation().distance(ninja->getLocation()) <= 1) {
                ninja->slash(target);
            } else {
                ninja->move(target);
            }
        }
    }
}

int Team2::stillAlive() {
    int stillAlive = 0;
    for (const auto& element : getTeam()) {
        if (dynamic_cast<Cowboy *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
        if (dynamic_cast<Ninja *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
    }
    return stillAlive;
}


Character* Team2::closestToLeader(Character *Leader) {
    Point leader_location = Leader->getLocation();
    double dis = -1;
    Character* target = nullptr;
    for (auto &i: getTeam()) {
        if (i == nullptr) break;
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            if (!i->isAlive()) continue;//don't target dead
            if (dis == -1 || i->getLocation().distance(leader_location) < dis) {
                dis = i->getLocation().distance(leader_location);
                target = i;
            }
        }
        if (dynamic_cast<Ninja *>(i) != nullptr) {
            if (!i->isAlive())continue;//don't target dead
            if (dis == -1 || i->getLocation().distance(leader_location) < dis) {
                dis = i->getLocation().distance(leader_location);
                target = i;
            }
        }
    }
    return target;
}

