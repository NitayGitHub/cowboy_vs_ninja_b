#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Point.hpp"
using namespace std;

namespace ariel
{
    enum characterType
    {
        COWBOY = 0,
        NINJA = 1
    };

    class Character
    {
    private:
        characterType type;
        string name;
        Point location;
        int HealthPoints;
        bool inTeam = false;

    public:
        // Constructors
        Character(string name, Point location, int HealthPoints, characterType type);
        virtual ~Character();

        // Functions
        virtual bool isAlive() const;
        virtual void hit(int damage);
        virtual double distance(const Character* other) const;
        virtual string print() const = 0;
        virtual void attack(Character* other) = 0;

        // Getters and Setters
        string getName() const;
        characterType getType() const;
        Point getLocation() const;
        int getHP() const;
        void setName(string name);
        void setLocation(Point location);
        void setHP(int HealthPoints);
        bool isInTeam() const;
        void setInTeam(bool inTeam);
    };

}
#endif