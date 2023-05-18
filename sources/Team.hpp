
#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "Point.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"

constexpr size_t MAX_TEAM_SIZE = 10;

namespace ariel {}
class Team {
    Character* leader;
    std::vector<Character*> team;
public:
    explicit Team(Character *leader);

    ~Team();

    Character* getLeader() const;
    void setLeader(Character* leader);
    vector<Character*>& getTeam();

    virtual void add(Character *newCharacter);

    virtual void attack(Team *enemy);

    virtual int stillAlive();

    virtual void print();

    virtual Character* closestToLeader(Character* Leader);
};


//class SmartTeam : public Team {
//public:
//    explicit SmartTeam(Character *leader);
//
//    void add(Character *newCharacter) override;
//
//    void attack(Team *enemy) override;
//
//    int stillAlive() override;
//
//    void print() override;
//
//    int findNearest(Character* leader) override;
//
//};


#endif //TEAM_H
