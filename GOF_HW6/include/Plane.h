#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() override;
    virtual void DrawBody() const = 0;
    virtual void DrawWings() const = 0 ;
    virtual void DrawTail() const = 0;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};

class ColorPlane : public Plane {
public:
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};

class BigPlane : public Plane {
public:
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};