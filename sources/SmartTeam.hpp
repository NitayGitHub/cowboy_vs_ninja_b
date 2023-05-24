#ifndef SMARTTEAM_H
#define SMARTTEAM_H
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>
#include "Team.hpp"

using namespace std;

namespace ariel
{

    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *leader);
        void attack(Team *other) override;

        // Aid functions
        void efficientAttack(list<Character *> &attackTeam, Team *other); // find closest combination of attacks
        list<int> findClosestCombination(const list<int> &attacks, int targetHealth);
        Character *closestToLeader(Team *enemy) override; // if several enemies are at the same distance, choose the one with the lowest HP
    };

}

#endif