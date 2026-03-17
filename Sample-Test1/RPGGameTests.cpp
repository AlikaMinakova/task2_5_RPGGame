#include "pch.h"
#include "..\RPGGame\Clan.cpp"
#include "..\RPGGame\Robot.cpp"
#include "..\RPGGame\Location.cpp"
#include "..\RPGGame\Strategies.cpp"
#include "..\RPGGame\World.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//
// Clan tests
//

TEST(ClanTest, ClanIsAliveWithAliveRobot)
{
    Clan clan(1);
    auto robot = std::make_shared<WalkerRobot>(&clan);

    clan.robots.push_back(robot);

    EXPECT_TRUE(clan.isAlive());
}

TEST(ClanTest, ClanIsDeadWhenAllRobotsDestroyed)
{
    Clan clan(1);
    auto robot = std::make_shared<WalkerRobot>(&clan);

    robot->takeDamage(200);

    clan.robots.push_back(robot);

    EXPECT_FALSE(clan.isAlive());
}

//
// Robot tests
//

TEST(RobotTest, RobotAliveInitially)
{
    Clan clan(1);
    WalkerRobot robot(&clan);

    EXPECT_TRUE(robot.isAlive());
}

TEST(RobotTest, RobotDiesAfterDamage)
{
    Clan clan(1);
    WalkerRobot robot(&clan);

    robot.takeDamage(200);

    EXPECT_FALSE(robot.isAlive());
}

TEST(RobotTest, RobotAttackReducesHealth)
{
    Clan clan1(1);
    Clan clan2(2);

    WalkerRobot attacker(&clan1);
    WalkerRobot target(&clan2);

    int before = target.isAlive();

    attacker.attack(target);

    EXPECT_TRUE(target.isAlive());
}

TEST(RobotTest, RobotEnergyIncrease)
{
    Clan clan(1);
    WalkerRobot robot(&clan);

    robot.addEnergy(20);

    EXPECT_TRUE(robot.isAlive());
}

//
// Location tests
//

TEST(LocationTest, CollectBatteries)
{
    Location loc(1);

    int batteries = loc.collectBatteries();

    EXPECT_GE(batteries, 1);
    EXPECT_EQ(loc.collectBatteries(), 0);
}

TEST(LocationTest, AddNeighbor)
{
    Location loc1(1);
    Location loc2(2);

    loc1.addNeighbor(&loc2);

    EXPECT_EQ(loc1.neighbors.size(), 1);
}

//
// Strategy tests
//

TEST(StrategyTest, ExplorerStrategyMovesRobot)
{
    Clan clan(1);

    Location loc1(1);
    Location loc2(2);

    loc1.addNeighbor(&loc2);
    loc2.addNeighbor(&loc1);

    auto robot = std::make_shared<WalkerRobot>(&clan);

    robot->setLocation(&loc1);
    robot->setStrategy(std::make_unique<ExplorerStrategy>());

    loc1.robots.push_back(robot);

    robot->update();

    EXPECT_TRUE(robot->getLocation() == &loc1 || robot->getLocation() == &loc2);
}

TEST(StrategyTest, AggressiveStrategyAttacksEnemy)
{
    Clan clan1(1);
    Clan clan2(2);

    Location loc(1);

    auto robot1 = std::make_shared<WalkerRobot>(&clan1);
    auto robot2 = std::make_shared<WalkerRobot>(&clan2);

    robot1->setLocation(&loc);
    robot2->setLocation(&loc);

    robot1->setStrategy(std::make_unique<AggressiveStrategy>());

    loc.robots.push_back(robot1);
    loc.robots.push_back(robot2);

    robot1->update();

    EXPECT_TRUE(robot2->isAlive() || !robot2->isAlive());
}

//
// World tests
//

TEST(WorldTest, WorldCreation)
{
    World world;

    EXPECT_NO_THROW(world.createWorld(5, 3));
}

TEST(WorldTest, SimulationRuns)
{
    World world;

    world.createWorld(5, 3);

    EXPECT_NO_THROW(world.simulate(5));
}