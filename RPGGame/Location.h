#pragma once
#include <vector>
#include <memory>
#include "Declarations.h"

class Location
{
private:
    int id;
    int batteries;

public:
    std::vector<Location*> neighbors;
    std::vector<std::shared_ptr<Robot>> robots;

    Location(int id);

    int getId() const;
    int collectBatteries();
    void addNeighbor(Location* loc);
};