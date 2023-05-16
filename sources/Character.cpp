#include "Character.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{
    // Constructors and destructors

    Character:: Character(string name, Point location, int HealthPoints, characterType type) : name(name), location(location), HealthPoints(HealthPoints), type(type) {}

    Character:: ~Character() {}

    // Functions

    bool Character::isAlive() const
    {
        return HealthPoints > 0;
    }

    double Character::distance(const Character* other) const
    {
        return location.distance(other->getLocation());
    }

    void Character::hit(int damage)
    {
        if(damage < 0)
        {
            throw invalid_argument("Damage can't be negative");
        }
        if (!isAlive())
        {
            throw runtime_error("Character is dead");
        }
        HealthPoints -= damage;
    }

    // Getters and Setters

    string Character::getName() const
    {
        return name;
    }

    characterType Character::getType() const
    {
        return type;
    }

    Point Character::getLocation() const
    {
        return location;
    }

    int Character::getHP() const
    {
        return HealthPoints;
    }

    void Character::setName(string name)
    {
        this->name = name;
    }

    void Character::setLocation(Point location)
    {
        this->location = location;
    }

    void Character::setHP(int HealthPoints)
    {
        this->HealthPoints = HealthPoints;
    }

    bool Character::isInTeam() const
    {
        return inTeam;
    }

    void Character::setInTeam(bool inTeam)
    {
        this->inTeam = inTeam;
    }

}