#ifndef COWBOY_H
#define COWBOY_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Character.hpp"
using namespace std;

namespace ariel
{
    class Cowboy : public Character
    {
    private:
        int bullets;

    public:
        // Constructors
        Cowboy(string name, Point location);
        ~Cowboy() override;

        // Functions
        void shoot(Character* other);
        bool hasBullets() const;
        void reload();
        string print() const override;
        void attack(Character* other) override;

        // Getters and Setters
        int getBullets() const;
    };
}

#endif