#pragma once
#include "Declarations.h"

class IStrategy
{
public:
    virtual ~IStrategy() = default;
    virtual void execute(Robot& robot) = 0;
};

class ExplorerStrategy : public IStrategy
{
public:
    void execute(Robot& robot) override;
};

class AggressiveStrategy : public IStrategy
{
public:
    void execute(Robot& robot) override;
};