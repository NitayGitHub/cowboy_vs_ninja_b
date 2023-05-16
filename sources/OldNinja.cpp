#include "Ninja.hpp"
#include "OldNinja.hpp"
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{

    OldNinja::OldNinja(string name, Point location) : Ninja(name, location, 8, 150) {}

    OldNinja::~OldNinja() {}

}