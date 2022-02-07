#pragma once

#include "GameObject.h"

class AbstractCrater : public GameObject {
public:
    virtual ~AbstractCrater() = default;
    bool isInside(double xn) const;
};

class CommonCrater : public AbstractCrater {
public:
    void Draw() const;
};

class WinterCrater : public AbstractCrater {
public:
    void Draw() const;
};