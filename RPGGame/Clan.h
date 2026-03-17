#pragma once
#include <vector>
#include <memory>
#include "Declarations.h"

class Clan
{
private:
    int id;

public:
    std::vector<std::shared_ptr<Robot>> robots;

    Clan(int id);
    int getId() const;
    bool isAlive() const;
};