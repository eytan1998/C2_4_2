
#ifndef SMARTTEAM_H
#define SMARTTEAM_H

#include "Team.hpp"

/*
 * how to make smart team?
//prioritize
// 1. one we could kill
// 2. ninja can attack next turn
// 3. cob-oi
// 4. young (kill much you can and they faster...)
// 5. trained
// 6. old
// 7. less health
// 8. don't have bullets
 */

class SmartTeam : public Team {
public:
    explicit SmartTeam(Character *leader);

    void attack(Team *enemy) override;

    int stillAlive() override;

    Character *closestToLeader(Character *Leader) override;

    static Character *chooseTarget(const vector<Character *>& mTeam, Team *enemy);

    static Character *whoToPick(const vector<Character *>& mTeam, Character *enemy1, Character *enemy2);

    static int calc_cowboy_dmg(const vector<Character *>& mTeam);

    static int calc_ninja_dmg(const vector<Character *>& mTeam, Character *enemy);

};


#endif //SMARTTEAM_H
