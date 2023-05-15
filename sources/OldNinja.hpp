#ifndef OLDNINJA_H
#define OLDNINJA_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Character.hpp"
using namespace std;

namespace ariel
{

    class OldNinja : public Ninja
    {
    public:
        OldNinja(string name, Point location);
    };
    
}

#endif