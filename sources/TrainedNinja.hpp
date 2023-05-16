#ifndef TRAINEDNINJA_H
#define TRAINEDNINJA_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Ninja.hpp"
using namespace std;

namespace ariel
{
     class TrainedNinja : public Ninja
    {
    public:
        TrainedNinja(string name, Point location);
        ~TrainedNinja() override;
    };
    
}

#endif