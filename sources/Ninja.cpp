#include "Ninja.hpp"
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{
    // Constructors
    Ninja::Ninja(string name, Point location, int speed, int HealthPoints) : Character(name, location, HealthPoints, NINJA), speed(speed) {}

    Ninja::~Ninja() {}
    
    // Functions
    void Ninja::move(Character* other)
    {
        if (!isAlive())
        {
            throw runtime_error("Can't move when you're dead");
        }
        double charactersDistance = getLocation().distance(other->getLocation());
        double distanceToMove = (speed < charactersDistance) ? speed : charactersDistance;
        setLocation(Point::moveTowards(getLocation(), other->getLocation(), distanceToMove));
    }

    void Ninja::slash(Character* other)
    {
        if(other == this){
            throw runtime_error("Can't slash yourself");
        }
        if (!isAlive())
        {
            throw runtime_error("Can't attack when you're dead");
        }
        if (!other->isAlive())
        {
            throw runtime_error("Target Character is dead");
        }
        if (getLocation().distance(other->getLocation()) > 1)
        {
            //cout << "Target " << other->getName() << " is too far away from " << getName() << endl;
            return;
        }
        other->hit(40);
    }

    int Ninja::getSpeed() const
    {
        return speed;
    }

    string Ninja::print() const
    {
        if (getHP() <= 0)
        {
            return "Name: ((N)" + getName() + ")";
        }
        return "Name: (N) " + getName() + ". Health Points: " + to_string(getHP()) + ". Location: " + getLocation().toString();
    }

    void Ninja::attack(Character* other){
        if (!isAlive())
        {
            throw runtime_error("Can't attack when you're dead");
            return;
        }
        if (!other->isAlive())
        {
            throw runtime_error("Target Character is dead");
            return;
        }
        if (getLocation().distance(other->getLocation()) > 1)
        {
            move(other);
            return;
        }
        slash(other);
    }

}