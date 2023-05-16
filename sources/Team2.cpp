#include "Team2.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

namespace ariel
{

    Team2::Team2(Character *leader) : Team(leader) {}

    void Team2::add(Character *fighter)
    {
        if (getTeam()->size() == 10)
        {
            throw runtime_error("Team is full");
        }
        if(fighter->isInTeam()){
            throw runtime_error("Character is already in a team");
        }
        getTeam()->push_back(fighter);
        fighter->setInTeam(true);
    }

}
