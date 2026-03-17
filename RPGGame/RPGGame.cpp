#include "World.h"
#include <iostream>

int main()
{
    World world;

    int locations = 5;
    int clans = 3;

    world.createWorld(locations, clans);
    world.simulate(50);

    std::cout << "Simulation finished.\n";
    return 0;
}