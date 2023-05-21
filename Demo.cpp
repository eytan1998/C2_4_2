/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>

using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/Team2.hpp" //no need for other includes
#include "sources/SmartTeam.hpp"
#include <random>
#include <chrono>

using namespace ariel;

double random_float(double min = -100, double max = 100) {
    std::default_random_engine generator(
            static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

int random_int(double min = 0, double max = 2) {
    std::default_random_engine generator(
            static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

auto create_yninja = [](double x = random_float(), double y = random_float()) {
    return new YoungNinja{"Bob", Point{x, y}};
};

auto create_tninja = [](double x = random_float(), double y = random_float()) {
    return new TrainedNinja{"Bob", Point{x, y}};
};

auto create_oninja = [](double x = random_float(), double y = random_float()) {
    return new OldNinja{"Bob", Point{x, y}};
};

auto create_cowboy = [](double x = random_float(), double y = random_float()) {
    return new Cowboy{"Bob", Point{x, y}};
};

int main() {

//    Point a(32.3,44),b(1.3,3.5);
//    assert(a.distance(b) == b.distance(a));
//    Cowboy *tom = new Cowboy("Tom", a);
//    OldNinja *sushi = new OldNinja("sushi", b);
//    tom->shoot(sushi);
//    cout << tom->print() <<endl;
//
//    sushi->move(tom);
//    sushi->slash(tom);
//
//    Team team_A(tom);
//    team_A.add(new YoungNinja("Yogi", Point(64,57)));
//
//    // Team b(tom); should throw tom is already in team a
//
//     Team team_B(sushi);
//     team_B.add(new TrainedNinja("Hikari", Point(12,81)));
//
//
//     while(team_A.stillAlive() > 0 && team_B.stillAlive() > 0){
//        team_A.attack(&team_B);
//        team_B.attack(&team_A);
//        team_A.print();
//        team_B.print();
//     }
//
//     if (team_A.stillAlive() > 0) cout << "winner is team_A" << endl;
//     else cout << "winner is team_B" << endl;

    int teamA_WINS = 0;
    int teamB_WINS = 0;
    for (int i = 0; i < 10000; ++i) {
        Team2 team_A(new Cowboy("c1", {random_float(), random_float()}));
        SmartTeam team_B(new Cowboy("c2", {random_float(), random_float()}));

        int numCowboy = random_int(0,9);
        for (int j = 0; j < numCowboy; ++j) {
            team_A.add(create_cowboy());
            team_B.add(create_cowboy());
        }

        ///
        int numYoung = random_int(0,9-numCowboy);
        for (int j = 0; j < numYoung; ++j) {
            team_A.add(create_yninja());
            team_B.add(create_yninja());
        }

        ///
        int numTrained = random_int(0,9-numCowboy-numYoung);
        for (int j = 0; j < numTrained; ++j) {
            team_A.add(create_tninja());
            team_B.add(create_tninja());
        }

        ///
        int numOld = random_int(0,9-numCowboy-numYoung-numTrained);
        for (int j = 0; j < numOld; ++j) {
            team_A.add(create_oninja());
            team_B.add(create_oninja());
        }

        while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0) {
            if(random_int(0,2)>=1){
                team_A.attack(&team_B);
                team_B.attack(&team_A);
            }else{
                team_B.attack(&team_A);
                team_A.attack(&team_B);
            }
        }

        if (team_A.stillAlive() > 0) teamA_WINS++;
        else teamB_WINS++;
    }
    if (teamA_WINS > teamB_WINS) cout << "winner is team_A :" << (teamA_WINS*1.0 / (teamA_WINS + teamB_WINS))*100<<"%" << endl;
    else if (teamA_WINS < teamB_WINS)
        cout << "winner is team_B :" << (teamB_WINS*1.0 / (teamA_WINS + teamB_WINS))*100<<"%" << endl;
    else cout << "Draw" << endl;
    return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.

}
