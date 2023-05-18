//
//#include "Team.hpp"
//
//SmartTeam::SmartTeam(Character *leader) : Team(leader){}
//
//void SmartTeam::add(Character *newCharacter)  {
//    if (index >= MAX_TEAM_SIZE) throw std::runtime_error("team cant be more than 10");
//    team[index++] = newCharacter;
//}
//
//void SmartTeam::attack(Team *enemy) {
//    //set new leader if needed
//    if (!team[leader]->isAlive()) {
//        int newleader = findNearest();
//        if (newleader == -1)return;
//        leader = newleader;
//    }
//    int closest_enemy = enemy->findNearest();
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Cowboy *>(team[i]) != nullptr) {
//            if (!enemy->team[closest_enemy]->isAlive()) {
//                closest_enemy = enemy->findNearest();
//            }
//            Cowboy *cowboy = dynamic_cast<Cowboy *>(team[i]);
//            if (cowboy->hasboolets()) {
//                cowboy->shoot(enemy->team[closest_enemy]);
//            } else {
//                cowboy->reload();
//            }
//        }
//    }
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Ninja *>(team[i]) != nullptr) {
//            if (!enemy->team[closest_enemy]->isAlive()) {
//                closest_enemy = enemy->findNearest();
//            }
//            Ninja *ninja = dynamic_cast<Ninja *>(team[i]);
//            if (enemy->team[closest_enemy]->getLocation().distance(ninja->getLocation()) < 1) {
//                ninja->slash(enemy->team[closest_enemy]);
//            } else {
//                ninja->move(enemy->team[closest_enemy]);
//            }
//        }
//    }
//}
//
//int SmartTeam::stillAlive() {
//    int stillAlive = 0;
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Cowboy *>(team[i]) != nullptr) {
//            if(team[i]->isAlive())stillAlive++;
//        }
//    }
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Ninja *>(team[i]) != nullptr) {
//            if(team[i]->isAlive())stillAlive++;
//        }
//    }
//    return stillAlive;
//}
//
//void SmartTeam::print() {
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Cowboy *>(team[i]) != nullptr) {
//            team[i]->print();
//        }
//    }
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (dynamic_cast<Ninja *>(team[i]) != nullptr) {
//            team[i]->print();
//        }
//    }
//}
//
//int SmartTeam::findNearest(Character* leader) {
//    Point leader_point = team[leader]->getLocation();
//    int Nearest = leader;
//    double min_dis = 0;
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (i == leader || !team[i]->isAlive())continue;
//        if (dynamic_cast<Cowboy *>(team[i]) != nullptr) {
//            if (Nearest == leader || team[i]->getLocation().distance(leader_point) < min_dis) {
//                min_dis = team[i]->getLocation().distance(leader_point);
//                Nearest = i;
//            }
//
//        }
//    }
//    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
//        if (team[i] == NULL) break;
//        if (i == leader || !team[i]->isAlive())continue;
//        if (dynamic_cast<Ninja *>(team[i]) != nullptr) {
//            if (Nearest == leader || team[i]->getLocation().distance(leader_point) < min_dis) {
//                min_dis = team[i]->getLocation().distance(leader_point);
//                Nearest = i;
//            }
//        }
//    }
//    return Nearest;
//}
//
