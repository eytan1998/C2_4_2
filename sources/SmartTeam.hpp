
#ifndef SMARTTEAM_H
#define SMARTTEAM_H

#include "Team.hpp"

/*
 * how to make smart team?
 * loop:
 * 1. if more cab-oi then them so jut shoot, if ninja can slash so slash
 * 2. else (need to kill them fast) prioritize (one we could kill) > cob-oi > young > trained  > old
 */

class SmartTeam : public Team {
public:
    explicit SmartTeam(Character *leader);

    void attack(Team *enemy) override;

    int stillAlive() override;

    Character *closestToLeader(Character *Leader) override;

    bool haveMoreCowboy(Team *enemy);

    static Character *chooseTarget(const vector<Character *>& mTeam, Team *enemy);

    static Character *whoToPick(const vector<Character *>& mTeam, Character *enemy1, Character *enemy2);

    static int calc_cowboy_dmg(const vector<Character *>& mTeam);

    static int calc_ninja_dmg(const vector<Character *>& mTeam, Character *enemy);

};


#endif //SMARTTEAM_H
