#include "World.h"
#include "Robot.h"
#include "Strategies.h"
#include "Utils.h"
#include <iostream>

void World::createWorld(int locationCount, int clanCount)
{
    for (int i = 0; i < locationCount; i++)
        locations.push_back(std::make_unique<Location>(i));

    for (int i = 0; i < locationCount - 1; i++)
    {
        locations[i]->addNeighbor(locations[i + 1].get());
        locations[i + 1]->addNeighbor(locations[i].get());
    }

    for (int i = 0; i < clanCount; i++)
    {
        clans.push_back(std::make_unique<Clan>(i));

        auto robot = std::make_shared<WalkerRobot>(clans[i].get());
        robot->setStrategy(std::make_unique<AggressiveStrategy>());
        robot->setLocation(locations[randomInt(0, locationCount - 1)].get());

        clans[i]->robots.push_back(robot);
        robot->getLocation()->robots.push_back(robot);
    }
}

void World::simulate(int steps)
{
    for (int s = 0; s < steps; s++)
    {
        std::cout << "\n=== Step " << s + 1 << " ===\n";
        for (auto& clan : clans)
            for (auto& robot : clan->robots)
                if (robot->isAlive())
                    robot->update();
        // Проверка победы
        int aliveClans = 0;
        int lastAliveClan = -1;
        for (auto& clan : clans)
        {
            if (clan->isAlive())
            {
                aliveClans++;
                lastAliveClan = clan->getId();
            }
        }
        if (aliveClans <= 1)
        {
            std::cout << "\nSimulation ended early. Clan " << lastAliveClan << " wins!\n";
            return;
        }
    }

    std::cout << "\nSimulation finished. No clear winner.\n";
}