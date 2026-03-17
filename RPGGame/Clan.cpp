#include "Clan.h"
#include "Robot.h"

Clan::Clan(int id) : id(id) {}

int Clan::getId() const { return id; }

bool Clan::isAlive() const
{
    for (auto& r : robots)
        if (r->isAlive()) return true;
    return false;
}