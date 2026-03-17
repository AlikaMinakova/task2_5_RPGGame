#include "Location.h"
#include "Utils.h"

Location::Location(int id) : id(id)
{
    batteries = randomInt(1, 5);
}

int Location::getId() const { return id; }

int Location::collectBatteries()
{
    int b = batteries;
    batteries = 0;
    return b;
}

void Location::addNeighbor(Location* loc)
{
    neighbors.push_back(loc);
}