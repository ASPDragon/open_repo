#include "House.h"
#include <iostream>
#include "ScreenSingleton.h"

bool House::HandleInsideCheck(double x1, double x2) const
{
    const double XBeg = x + 2;
    const double XEnd = x + width - 1;

    if (x1 < XBeg && x2 > XEnd)
    {
        return true;
    }

    if (x1 > XBeg && x1 < XEnd)
    {
        return true;
    }

    if (x2 > XBeg && x2 < XEnd)
    {
        return true;
    }

    return false;
}

void House::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_Yellow);
    ScreenSingleton::getInstance().GotoXY(x, y - 6);
    std::cout << look[0];
    ScreenSingleton::getInstance().GotoXY(x, y - 5);
    std::cout << look[1];
    ScreenSingleton::getInstance().GotoXY(x, y - 4);
    std::cout << look[2];
    ScreenSingleton::getInstance().GotoXY(x, y - 3);
    std::cout << look[3];
    ScreenSingleton::getInstance().GotoXY(x, y - 2);
    std::cout << look[4];
    ScreenSingleton::getInstance().GotoXY(x, y - 1);
    std::cout << look[5];
    ScreenSingleton::getInstance().GotoXY(x, y);
    std::cout << look[6];
}
