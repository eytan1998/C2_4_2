
#include "Team.hpp"


Team::Team(Character *leader) : leader(leader){
    if (leader->isBusy()) throw std::runtime_error("cant be more than one team");
    team.push_back(leader);
    leader->joinTeam();
}

Team::~Team() {
    for (auto &i: team) {
        if (i == nullptr) break;
        delete i;
    }
}

Character* Team::getLeader() const {
    return leader;
}
void Team::setLeader(Character* lead) {
    leader = lead;
}


vector<Character *>& Team::getTeam() {
    return team;
}


void Team::add(Character *newCharacter) {
    if (getTeam().size() >=  MAX_TEAM_SIZE) throw std::runtime_error("team cant be more than 10");
    if (newCharacter->isBusy()) throw std::runtime_error("cant be more than one team");
    team.push_back(newCharacter);
    newCharacter->joinTeam();
}

void Team::attack(Team *enemy) {
    if (enemy == nullptr) throw std::invalid_argument("null");
    if (enemy->stillAlive() <= 0) throw std::runtime_error("Cant fight the dead");

    //set new leader if needed
    if (!getLeader()->isAlive()) {
        Character* closest = closestToLeader(getLeader());//won't send leader because is dead
        if (closest == nullptr) return; // team dead
        leader = closest;
    }

    Character* target;
    for (auto &i: team) {
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
    }
    for (auto &i: team) {
        if (i == nullptr) break;
        if (!i->isAlive()) continue;
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

int Team::stillAlive() {
    int stillAlive = 0;

    for (const auto& element : getTeam()) {

        if (element == nullptr) continue;
        if (dynamic_cast<Cowboy *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
    }
    for (const auto& element : getTeam()) {
        if (element == nullptr) continue;
        if (dynamic_cast<Ninja *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
    }
    return stillAlive;
}

void Team::print() {
    const std::type_info& type = typeid(*this);

    cout<<"################"<<type.name()<< " Print################"<<endl;
    for (auto &i: team) {
        if (i == nullptr) break;
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            cout<<i->print();
        }
    }
    for (auto &i: team) {
        if (i == nullptr) break;
        if (dynamic_cast<Ninja *>(i) != nullptr) {
            cout<<i->print();
        }
    }
    cout<<endl;

}


Character* Team::closestToLeader(Character *Leader) {
    Point leader_location = Leader->getLocation();
    double dis = -1;
    Character* target = nullptr;
    for (auto &i: team) {
        if (i == nullptr) break;
        if (!i->isAlive()) continue;//don't target dead
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            if (dis == -1 || i->getLocation().distance(leader_location) < dis) {
                dis = i->getLocation().distance(leader_location);
                target = i;
            }
        }
    }
    for (auto &i: team) {
        if (i == nullptr) break;
        if (!i->isAlive()) continue;//don't target dead
        if (dynamic_cast<Ninja *>(i) != nullptr) {
            if (dis == -1 || i->getLocation().distance(leader_location) < dis) {
                dis = i->getLocation().distance(leader_location);
                target = i;
            }
        }
    }

    return target;
}



