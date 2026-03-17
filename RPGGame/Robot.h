#pragma once
#include <memory>
#include "Strategies.h"
#include "Clan.h"
#include "Location.h"

class Robot
{
protected:
    int health;
    int energy;
    int damage;
    int range;

    Clan* clan;
    Location* location;
    std::unique_ptr<IStrategy> strategy;

public:
    Robot(int hp, int en, int dmg, int range, Clan* clan);

    virtual ~Robot() = default;

    void setStrategy(std::unique_ptr<IStrategy> strat);
    void setLocation(Location* loc);

    bool isAlive() const;
    Clan* getClan() const;
    Location* getLocation() const;

    virtual void move();
    virtual void attack(Robot& target);
    virtual void update();

    void takeDamage(int dmg);
    void addEnergy(int val);
};

class WalkerRobot : public Robot
{
public:
    WalkerRobot(Clan* clan)
        : Robot(100, 50, 15, 1, clan) {
    }
};

class SpiderRobot : public Robot
{
public:
    SpiderRobot(Clan* clan)
        : Robot(80, 60, 10, 2, clan) {
    }
};

class WheeledRobot : public Robot
{
public:
    WheeledRobot(Clan* clan)
        : Robot(120, 40, 20, 1, clan) {
    }
};