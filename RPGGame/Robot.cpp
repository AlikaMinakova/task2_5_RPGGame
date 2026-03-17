#include "Robot.h"
#include "Location.h"
#include "Strategies.h"
#include <iostream>

Robot::Robot(int hp, int en, int dmg, int range, Clan* clan)
    : health(hp), energy(en), damage(dmg), range(range), clan(clan), location(nullptr)
{
}

void Robot::setStrategy(std::unique_ptr<IStrategy> strat)
{
    strategy = std::move(strat);
}

void Robot::setLocation(Location* loc)
{
    location = loc;
}

bool Robot::isAlive() const { return health > 0; }
Clan* Robot::getClan() const { return clan; }
Location* Robot::getLocation() const { return location; }

void Robot::move()
{
    if (!location || location->neighbors.empty() || energy <= 0) return;

    Location* next = location->neighbors[rand() % location->neighbors.size()];
    std::cout << "Robot from Clan " << clan->getId() << " moves from Location "
        << location->getId() << " to Location " << next->getId() << "\n";

    location = next;
    energy -= 1;
}

void Robot::attack(Robot& target)
{
    if (energy <= 0) return;
    std::cout << "Robot from Clan " << clan->getId()
        << " attacks Robot from Clan " << target.getClan()->getId() << " dealing "
        << damage << " damage.\n";
    target.takeDamage(damage);
    energy -= 2;

    if (!target.isAlive())
        std::cout << "Robot from Clan " << target.getClan()->getId() << " is destroyed!\n";
}

void Robot::update()
{
    if (strategy)
        strategy->execute(*this);
}

void Robot::takeDamage(int dmg)
{
    health -= dmg;
}

void Robot::addEnergy(int val)
{
    energy += val;
}