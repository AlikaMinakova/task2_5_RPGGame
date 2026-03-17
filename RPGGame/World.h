#pragma once
#include <vector>
#include <memory>
#include "Location.h"
#include "Clan.h"

class World
{
private:
    std::vector<std::unique_ptr<Location>> locations;
    std::vector<std::unique_ptr<Clan>> clans;

public:
    void createWorld(int locationCount, int clanCount);
    void simulate(int steps);
};