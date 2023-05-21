
#ifndef TEAM2_H
#define TEAM2_H

#include "Team.hpp"


class Team2 : public Team {
public:
    explicit Team2(Character *leader);

    void attack(Team *enemy) override;

    int stillAlive() override;

    Character* closestToLeader(Character* Leader) override;
};


#endif //TEAM2_H
