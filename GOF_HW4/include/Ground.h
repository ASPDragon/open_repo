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
    Ground(const ConsoleColor &color) : color{color} {}
    void AddCrater(double xn);
    virtual AbstractCrater* CreateCrater() const = 0;
    void Draw() const override;

protected:
    bool isInsideAnyCrater(double x) const;
    const ConsoleColor &color;
    std::vector<AbstractCrater*> vecCrates;
};

class WinterGround : public Ground {
public:
    WinterGround() : Ground(CC_White) {}
    AbstractCrater* CreateCrater() const override;
};

class CommonGround : public Ground {
public:
    CommonGround() : Ground(CC_Green) {}
    AbstractCrater* CreateCrater() const override;
};