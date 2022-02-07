#pragma once

#include "GameObject.h"
#include "Crater.h"
#include <vector>
#include "ScreenSingleton.h"

class IGround : public GameObject {
public:
    IGround() = default;
    virtual ~IGround() = default;
};

class Ground : public IGround {
public:
    Ground(const ConsoleColor color, const CraterSize size) : color{color}, size{size} {}
    virtual void AddCrater(double xn);
    virtual AbstractCrater* CreateCrater() const = 0;
    void Draw() const override;

protected:
    bool isInsideAnyCrater(double x) const;
    const ConsoleColor color;
    const CraterSize size;
    std::vector<AbstractCrater*> vecCrates;
};

class WinterGround : public Ground {
public:
    WinterGround() : Ground(CC_White, BIG_CRATER_SIZE) {}
    AbstractCrater* CreateCrater() const override;
};

class CommonGround : public Ground {
public:
    CommonGround() : Ground(CC_Green, SMALL_CRATER_SIZE) {}
    AbstractCrater* CreateCrater() const override;
};