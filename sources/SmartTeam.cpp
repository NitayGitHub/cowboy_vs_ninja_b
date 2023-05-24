#include "SmartTeam.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <list>
using namespace std;
namespace ariel
{

    SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

    Character *SmartTeam::closestToLeader(Team *enemy)
    {
        int minDistance = -1;
        Character *closest = nullptr;
        for (auto it = enemy->getTeam().begin(); it != enemy->getTeam().end(); it++)
        {
            if (!((*it)->isAlive()))
            {
                continue;
            }

            int distance = getLeader()->distance(*it);
            if (minDistance == -1 || distance < minDistance)
            {
                minDistance = distance;
                closest = *it;
            }
            else if (distance == minDistance && (*it)->getHP() < closest->getHP())
            {
                closest = *it;
            }
        }

        return closest;
    }

    void SmartTeam::attack(Team *other)
    {
        efficientAttack(getTeam(), other);
    }

    void SmartTeam::efficientAttack(list<Character *> &attackTeam, Team *other)
    {
        if (!canAtkTeam(other))
        {
            return;
        }

        // find the closest enemy to the leader
        Character *closest = closestToLeader(other);
        if (closest == nullptr)
        {
            cout << "closest is nullptr" << endl;
        }

        // gather all attacks that can be done
        list<int> attacks;
        list<Character *> attackers;

        for (auto it = attackTeam.begin(); it != attackTeam.end(); it++)
        {
            if (!((*it)->isAlive()))
            {
                continue;
            }
            if ((*it)->getType() == COWBOY)
            {
                Cowboy *c = dynamic_cast<Cowboy *>(*it);
                if (c->hasboolets())
                {
                    attacks.push_back(10);
                    attackers.push_back(*it);
                }
                else
                {
                    c->reload();
                    cout << "reloading" << endl;
                }
            }
            else if ((*it)->getType() == NINJA)
            {
                Ninja *n = dynamic_cast<Ninja *>(*it);
                if (n->getLocation().distance(closest->getLocation()) <= 1)
                {
                    attacks.push_back(40);
                    attackers.push_back(*it);
                }
                else
                {
                    n->move(closest);
                }
            }
        }

        // find the closest combination of attacks to the target's health
        list<int> closestCombo = findClosestCombination(attacks, closest->getHP());

        // print combo attack on closest
        cout << "Attacks on " << closest->getName() << ": ";
        for (auto it = closestCombo.begin(); it != closestCombo.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;

        // attack with combination attackers
        for (auto it = closestCombo.begin(); it != closestCombo.end(); it++)
        {
            if ((*it) == 10)
            {
                auto attacker = find_if(attackers.begin(), attackers.end(), [](Character *c)
                                        { return c->getType() == COWBOY; });
                Character *c = dynamic_cast<Cowboy *>(*attacker);
                c->attack(closest);
                attackers.remove(c);
            }
            else if ((*it) == 40)
            {
                auto attacker = find_if(attackers.begin(), attackers.end(), [](Character *c)
                                        { return c->getType() == NINJA; });
                Character *n = dynamic_cast<Ninja *>(*attacker);
                n->attack(closest);
                attackers.erase(attacker);
            }
        }

        // if there are still attackers left, closest is dead. Redo with left attackers
        if (attackers.size() > 0)
        {
            efficientAttack(attackers, other);
        }
    }

    list<int> SmartTeam::findClosestCombination(const list<int> &attacks, int targetHealth)
    {
        // gather all attacks greater than target health
        list<int> greaterAttacks;
        for (auto it = attacks.begin(); it != attacks.end(); it++)
        {
            if ((*it) > targetHealth)
            {
                greaterAttacks.push_back(*it);
            }
        }

        // if true, the weakest attack
        if (greaterAttacks.size() == attacks.size())
        {
            list<int> weakest;
            weakest.push_back(*min_element(attacks.begin(), attacks.end()));
            return weakest;
        }

        int n = attacks.size();

        // Create a 1D dynamic programming array
        vector<bool> dp(static_cast<unsigned long>(targetHealth + 1));

        // Initialize the array
        dp[0] = true;

        // Fill the dynamic programming array
        for (int price : attacks)
        {
            for (int j = targetHealth; j >= price; j--)
            {
                dp[static_cast<unsigned long>(j)] = dp[static_cast<unsigned long>(j)] || dp[static_cast<unsigned long>(j - price)];
            }
        }

        // Find the closest sum
        int closestSum = -1;
        for (int j = targetHealth; j >= 0; j--)
        {
            if (dp[static_cast<unsigned long>(j)])
            {
                closestSum = j;
                break;
            }
        }

        // Find the items that contribute to the closest sum
        list<int> closestCombination;
        int remainingSum = closestSum;
        for (auto it = attacks.rbegin(); it != attacks.rend() && remainingSum > 0; ++it)
        {
            int price = *it;
            if (remainingSum >= price && dp[static_cast<unsigned long>(remainingSum - price)])
            {
                closestCombination.push_front(price);
                remainingSum -= price;
            }
        }

        // if there are greater attacks, check if they are closer to target health than the closest sum
        if (greaterAttacks.size() > 0)
        {
            int minGreater = *min_element(greaterAttacks.begin(), greaterAttacks.end());
            if (minGreater - targetHealth < targetHealth - closestSum)
            {
                closestCombination.clear();
                closestCombination.push_back(minGreater);
            }
        }

        return closestCombination;
    }

}