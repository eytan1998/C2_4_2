
#include "SmartTeam.hpp"

SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

void SmartTeam::attack(Team *enemy) {

    if (enemy == nullptr) throw std::invalid_argument("null");
    if (enemy->stillAlive() <= 0) throw std::runtime_error("Cant fight the dead");

    //set new leader if needed
    if (!getLeader()->isAlive()) {
        Character *closest = closestToLeader(getLeader());//won't send leader because is dead
        if (closest == nullptr) return; // team dead
        setLeader(closest);
    }

    //tmp list of alive team, to calc next target
    std::vector<Character *> tmpTeam;
    for (auto &i: getTeam()) {
        if (i->isAlive())
            tmpTeam.push_back(i);
    }
    Character *target = chooseTarget(tmpTeam, enemy);
    if (target == nullptr) return;

    for (auto &i: getTeam()) {
        if (!target->isAlive()) {
            target = chooseTarget(tmpTeam, enemy);
            if (target == nullptr) return;
        }
        //if not alive continue (not in tmp list)
        if (!i->isAlive()) continue;
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            auto *cowboy = dynamic_cast<Cowboy *>(i);
            if (!cowboy->hasboolets()) cowboy->reload();
            else cowboy->shoot(target);
            tmpTeam.erase(std::remove(tmpTeam.begin(), tmpTeam.end(), i), tmpTeam.end());

        } else if (dynamic_cast<Ninja *>(i) != nullptr) {
            auto *ninja = dynamic_cast<Ninja *>(i);
            //if you can slash main target do it
            if (ninja->distance(target) <= 1){
                ninja->slash(target);
                tmpTeam.erase(std::remove(tmpTeam.begin(), tmpTeam.end(), i), tmpTeam.end());
                continue;
            }
            else {
                //else find other if none stay
                for (auto &j: enemy->getTeam()) {
                    if(!j->isAlive())continue;
                    if (ninja->distance(j) <= 1) {
                        ninja->slash(j);
                        tmpTeam.erase(std::remove(tmpTeam.begin(), tmpTeam.end(), i), tmpTeam.end());
                        continue;
                    }
                }

                ninja->move(target);
                tmpTeam.erase(std::remove(tmpTeam.begin(), tmpTeam.end(), i), tmpTeam.end());

            }
        }

    }
}

int SmartTeam::stillAlive() {
    int stillAlive = 0;
    for (const auto &element: getTeam()) {
        if (dynamic_cast<Cowboy *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
        if (dynamic_cast<Ninja *>(element) != nullptr) {
            if (element->isAlive())stillAlive++;
        }
    }
    return stillAlive;
}


Character *SmartTeam::closestToLeader(Character *Leader) {
    Point leader_location = Leader->getLocation();
    double dis = -1;
    Character *target = nullptr;
    for (auto &i: getTeam()) {
        if (i == nullptr) break;
        if (!i->isAlive()) continue;//don't target dead
        if (dis == -1 || i->getLocation().distance(leader_location) < dis) {
            dis = i->getLocation().distance(leader_location);
            target = i;
        }

    }
    return target;
}

Character *SmartTeam::chooseTarget(const vector<Character *> &mTeam, Team *enemy) {
    Character *target = nullptr;
    for (auto &iEnemy: enemy->getTeam()) {
        if (!iEnemy->isAlive()) continue; // don't bother the dead
        target = whoToPick(mTeam, target, iEnemy);
    }
    return target;

}

int SmartTeam::calc_cowboy_dmg(const vector<Character *> &mTeam) {
    int dmg = 0;
    for (auto &i: mTeam) {
        if (i == nullptr) break;
        if (dynamic_cast<Cowboy *>(i) != nullptr) {
            auto *cowboy = dynamic_cast<Cowboy *>(i);
            if (cowboy->hasboolets())
                dmg += COWBOY_DMG;
        }
    }
    return dmg;
}

int SmartTeam::calc_ninja_dmg( const vector<Character *> &mTeam, Character *enemy) {
    int dmg = 0;
    for (auto &i: mTeam) {
        if (dynamic_cast<Ninja *>(i) != nullptr) {
            if (i->distance(enemy) <= 1) {
                dmg += NINJA_DMG;
            }
        }
    }
    return dmg;
}

//prioritize
// 1. one we could kill
// 2. ninja can attack next turn
// 3. cob-oi
// 4. young (kill much you can and they faster...)
// 5. trained
// 6. old
// 7. less health
// 8. don't have bullets
Character *SmartTeam::whoToPick(const vector<Character *>& mTeam, Character *enemy1, Character *enemy2) {
    if (enemy2 == nullptr) return enemy1;
    if (enemy1 == nullptr) return enemy2;
    //enemy1 can 1-shot
    int cowboy_dmg = calc_cowboy_dmg(mTeam);
    bool enemy1kill = enemy1->getHp() <= calc_ninja_dmg(mTeam, enemy1) + cowboy_dmg;
    bool enemy2kill = enemy2->getHp() <= calc_ninja_dmg(mTeam, enemy2) + cowboy_dmg;

    //return the one that kill
    if (enemy1kill && !enemy2kill)return enemy1;
    else if (!enemy1kill && enemy2kill)return enemy2;
    //compression num1 not in Q
    else {
        bool isCowboy1 = dynamic_cast<Cowboy *>(enemy1) != nullptr;
        bool isCowboy2 = dynamic_cast<Cowboy *>(enemy2) != nullptr;
        if (isCowboy1 && isCowboy2) {
            if (enemy1->getHp() > enemy2->getHp()) return enemy2;
            else if (enemy1->getHp() < enemy2->getHp()) return enemy1;

            //if equal health return the one with no bullets
            auto *cowboy1 = dynamic_cast<Cowboy *>(enemy1);
            auto *cowboy2 = dynamic_cast<Cowboy *>(enemy2);
            if (!cowboy1->hasboolets()) return cowboy1;
            return cowboy2; // choose 2 if equals till now
        }

        //one of each
            // cowboy > ninja, can attack > cowboy
        else if (!isCowboy1 && isCowboy2) {

            // 1 is ninja
            //calc if ninja can attack
            bool ninjaCanAttack = false;
            //if 1 can attack
            for (const auto &i: mTeam) {
                if (i->distance(enemy1) <= 1) {
                    ninjaCanAttack = true;
                }
            }


            //calc
            if (ninjaCanAttack)
                return enemy1; //ninja
            else return enemy2; // cowboy

        } else if (isCowboy1 && !isCowboy2) {

            // 2 is ninja
            //calc if ninja can attack
            bool ninjaCanAttack = false;
            //if 1 can attack
            for (const auto &i: mTeam) {
                if (i->distance(enemy2) <= 1) {
                    ninjaCanAttack = true;
                }
            }

            //calc
            if (ninjaCanAttack)
                return enemy2; //ninja
            else return enemy1; // cowboy

        } else {
            //both ninja, can attack > young > trained > old
            //calc if ninja can attack
            bool ninja1CanAttack = false;
            bool ninja2CanAttack = false;
            //if 1 can attack
            for (auto &i: mTeam) {
                if (i->distance(enemy1) <= 1) {
                    ninja1CanAttack = true;
                }
                if (i->distance(enemy2) <= 1) {
                    ninja2CanAttack = true;
                }
            }
            //one can attack
            if (ninja1CanAttack && !ninja2CanAttack)return enemy1;
            if (!ninja1CanAttack && ninja2CanAttack)return enemy2;
            //can both attack or cant
            bool isYoung1 = dynamic_cast<YoungNinja *>(enemy1) != nullptr;
            bool isYoung2 = dynamic_cast<YoungNinja *>(enemy2) != nullptr;

            bool isTrained1 = dynamic_cast<TrainedNinja *>(enemy1) != nullptr;
            bool isTrained2 = dynamic_cast<TrainedNinja *>(enemy2) != nullptr;

            bool isOld1 = dynamic_cast<OldNinja *>(enemy1) != nullptr;
            bool isOld2 = dynamic_cast<OldNinja *>(enemy2) != nullptr;
            //young > trained > old
            if ((isYoung1 && isTrained2) || (isYoung1 && isOld2) || (isTrained1 && isOld2))return enemy1;
            if ((isYoung2 && isTrained1) || (isYoung2 && isOld1) || (isTrained2 && isOld1))return enemy2;

            //same ninja up to health
            if (enemy1->getHp() > enemy2->getHp()) return enemy2;
            else return enemy1;
        }
    }
}

