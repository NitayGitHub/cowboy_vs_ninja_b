#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include <stdexcept>
#include <cmath>
using namespace std;
namespace ariel
{
    YoungNinja::YoungNinja(string name, Point location) : Ninja(name, location, 14, 100) {}
}