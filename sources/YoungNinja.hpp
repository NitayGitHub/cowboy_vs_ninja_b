#ifndef YOUNGNINJA_H
#define YOUNGNINJA_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Ninja.hpp"
using namespace std;

namespace ariel
{

    class YoungNinja : public Ninja
    {
    public:
        YoungNinja(string name, Point location);

        ~YoungNinja() override;
    };
    
}

#endif