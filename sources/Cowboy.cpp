#include "Cowboy.hpp"
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{
    // Constructors
    Cowboy::Cowboy(string name, Point location) : Character(name, location, 110, COWBOY), bullets(6) {}

    Cowboy::~Cowboy() {}

    // Functions
    void Cowboy::shoot(Character *other)
    {
        if (!hasboolets())
        {
            cout << "No bullets; reload first" << endl;
            return;
        }
        if (!isAlive())
        {
            throw runtime_error("Can't attack when you're dead");
        }
        if (!other->isAlive())
        {
            throw runtime_error("Target Character is dead");
        }
        other->hit(10);
        this->bullets--;
    }

    bool Cowboy::hasboolets() const
    {
        return bullets > 0;
    }

    void Cowboy::reload()
    {
        if (!isAlive())
        {
            throw runtime_error("Character is dead");
        }
        this->bullets = 6;
    }

    string Cowboy::print() const
    {
        if (getHP() <= 0)
        {
            return "Name: ((C)" + getName() + ")";
        }
        return "Name: (C) " + getName() + ". Health Points: " + to_string(getHP()) + ". Location: " + getLocation().toString();
    }

    // Getters and Setters
    int Cowboy::getBullets() const
    {
        return bullets;
    }

    void Cowboy::attack(Character *other)
    {
        if (!isAlive())
        {
            throw runtime_error("Can't attack when you're dead");
            return;
        }
        if(!other->isAlive()){
            throw runtime_error("Target Character is dead");
            return;
        }
        if (hasboolets()){
            reload();
        }
        shoot(other);
    }
}