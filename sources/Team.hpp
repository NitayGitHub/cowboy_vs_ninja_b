#ifndef TEAM_H
#define TEAM_H
#include <iostream>
#include <sstream>
#include <list>
#include <stdexcept>
#include "Character.hpp"
#include "Ninja.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"

using namespace std;

namespace ariel
{
    class Team
    {
    private:
        list<Character *> team;
        Character *leader;

    public:
        // Constructors and destructors
        Team(Character *leader);
        Team(Team &other);
        virtual ~Team();

        // operators
        Team &operator=(const Team &other);

        // Functions
        virtual void add(Character *fighter);
        virtual void attack(Team *other);
        void print();
        int stillAlive();

        // Extra functions
        bool isLeaderAlive();
        bool replaceLeader();
        virtual Character *closestToLeader(Team *enemy);
        Character* getLeader() const;
        list<Character *>& getTeam();
        int canAtkTeam(Team *other, bool throwIfEnemyDead);
    };

}
#endif