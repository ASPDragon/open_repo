
#include <iostream>

#include "Plane.h"
#include "MyTools.h"
#include "ScreenSingleton.h"

void Plane::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << "=========>";
    ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    std::cout << "===";
    ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    std::cout << "\\\\\\\\";
    ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    std::cout << "////";
}

void Plane::Accept(const Visitor& v) {
    v.log(*this);
}
