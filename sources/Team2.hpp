#ifndef TEAM2_H
#define TEAM2_H
#include <iostream>
#include <sstream>
#include <list>
#include <stdexcept>
#include "Team.hpp"

using namespace std;

namespace ariel
{

    class Team2 : public Team
    {
    public:
        Team2(Character *leader);
        void add (Character *fighter);
    };

}

#endif