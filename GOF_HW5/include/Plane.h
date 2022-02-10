#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;

    virtual void Accept(const Visitor& v);

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};

