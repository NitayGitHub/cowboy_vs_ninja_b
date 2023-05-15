#include "Team.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{
    // Constructors and operators
    Team::Team(Character *leader) : leader(leader)
    {
        if(leader->isInTeam()){
            throw invalid_argument("Character is already in a team");
        }
        team.push_back(leader);
        leader->setInTeam(true);
    }

    Team::Team(Team &other) : leader(other.leader)
    {
        for (list<Character *>::iterator it = other.team.begin(); it != other.team.end(); it++)
        {
            team.push_back(*it);
        }
    }

    Team::Team(Team &&other) : leader(other.leader)
    {
        for (list<Character *>::iterator it = other.team.begin(); it != other.team.end(); it++)
        {
            team.push_back(*it);
        }
    }

    Team2::Team2(Character *leader) : Team(leader) {}

    SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

    // Destructors
    Team::~Team()
    {
        for (list<Character *>::iterator it = team.begin(); it != team.end(); it++)
        {
            delete *it;
        }
    }

    // Functions
    void Team::add(Character *fighter)
    {
        if (team.size() == 10)
        {
            throw runtime_error("Team is full");
        }
        if(fighter->isInTeam()){
            throw runtime_error("Character is already in a team");
        }
        if (fighter->getType() == COWBOY)
        {
            team.push_front(fighter);
            fighter->setInTeam(true);
        }
        else if (fighter->getType() == NINJA)
        {
            team.push_back(fighter);
            fighter->setInTeam(true);
        }
    }

    void Team2::add(Character *fighter)
    {
        if (getTeam().size() == 10)
        {
            throw runtime_error("Team is full");
        }
        getTeam().push_back(fighter);
        fighter->setInTeam(true);
    }

    void SmartTeam::add(Character *fighter)
    {
        if (getTeam().size() == 10)
        {
            throw runtime_error("Team is full");
        }
        if (fighter->getType() == COWBOY)
        {
            getTeam().push_front(fighter);
            fighter->setInTeam(true);
        }
        else if (fighter->getType() == NINJA)
        {
            getTeam().push_back(fighter);
            fighter->setInTeam(true);
        }
    }

    bool Team::isLeaderAlive()
    {
        return leader->isAlive();
    }

    bool Team::replaceLeader()
    {
        int minDistance = -1;
        int newLeaderIndex = -1;
        for (list<Character *>::iterator it = team.begin(); it != team.end(); it++)
        {
            if (!((*it)->isAlive()))
            {
                continue;
            }
            if (minDistance == -1)
            {
                minDistance = leader->distance(*it);
                newLeaderIndex = distance(team.begin(), it);
                continue;
            }
            if (leader->distance(*it) < minDistance)
            {
                minDistance = leader->distance(*it);
                newLeaderIndex = distance(team.begin(), it);
            }
        }
        if (newLeaderIndex == -1)
        {
            return false;
        }
        list<Character *>::iterator it = team.begin();
        advance(it, newLeaderIndex);
        leader = *it;
        return true;
    }

    void Team::print()
    {
        for (list<Character *>::iterator it = team.begin(); it != team.end(); it++)
        {
            cout << (*it)->print() << endl;
        }
        cout << endl;
    }

    int Team::stillAlive()
    {
        int counter = 0;
        for (list<Character *>::iterator it = team.begin(); it != team.end(); it++)
        {
            if ((*it)->isAlive())
            {
                counter++;
            }
        }
        return counter;
    }

    Character* Team::closestToLeader(Team * enemy)
    {
        int minDistance = -1;
        Character *closest = nullptr;
        for (list<Character *>::iterator it = enemy->team.begin(); it != enemy->team.end(); it++)
        {
            if (!((*it)->isAlive()))
            {
                continue;
            }
            if (minDistance == -1)
            {
                minDistance = leader->distance(*it);
                closest = *it;
                continue;
            }
            if (leader->distance(*it) < minDistance)
            {
                minDistance = leader->distance(*it);
                closest = *it;
            }
        }
        return closest;
    }

    void Team::attack(Team *other)
    {
        if (!isLeaderAlive())
        {
            if (!replaceLeader())
            {
                cout << "The team has lost" << endl;
                return;
            }
        }
        if (!stillAlive())
        {
            throw runtime_error("Can't attack when your team is dead");
        }
        if (!other->stillAlive())
        {
            throw runtime_error("Can't attack a dead team");
        }
        
        Character *closest = closestToLeader(other);
        if(closest == nullptr){

            cout << "closest is nullptr" << endl;
        }
        
        for (list<Character *>::iterator it = team.begin(); it != team.end(); it++)
        {
            if (!((*it)->isAlive()))
            {
                
                continue;
            }
            if (!closest->isAlive() && !other->stillAlive())
            {
                return;
            }
            else if (!closest->isAlive())
            {
                closest = closestToLeader(other);
            }
            (*it)->attack(closest);
            
        }
    }

    // Getters and Setters

    Character *Team::getLeader() const
    {
        return leader;
    }

    list<Character *> Team::getTeam() const
    {
        return team;
    }

}