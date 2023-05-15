#ifndef NINJA_H
#define NINJA_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Character.hpp"
using namespace std;

namespace ariel
{
    // Ninja class
    class Ninja : public Character
    {
    private:
        int speed;

    public:
        // Constructors
        Ninja(string name, Point location, int speed, int HealthPoints);
        ~Ninja() override;

        // Functions
        virtual void move(Character* other);
        virtual void slash(Character* other);

        // Extra functions
        void attack(Character* other) override;
        int getSpeed() const;
        string print() const override;
    };
}

#endif