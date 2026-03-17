#include "Strategies.h"
#include "Robot.h"
#include "Location.h"
#include <iostream>

void ExplorerStrategy::execute(Robot& robot)
{
    std::cout << "Robot from Clan " << robot.getClan()->getId()
        << " explores.\n";
    robot.move();
}

void AggressiveStrategy::execute(Robot& robot)
{
    Location* loc = robot.getLocation();
    for (auto& other : loc->robots)
    {
        if (other.get() != &robot &&
            other->getClan() != robot.getClan() &&
            other->isAlive())
        {
            std::cout << "Robot from Clan " << robot.getClan()->getId()
                << " engages enemy in Location " << loc->getId() << "\n";
            robot.attack(*other);
            return;
        }
    }
    std::cout << "Robot from Clan " << robot.getClan()->getId()
        << " found no enemies and moves.\n";
    robot.move();
}