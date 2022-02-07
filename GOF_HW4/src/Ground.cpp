#include "Ground.h"
#include "Crater.h"
#include "ScreenSingleton.h"
#include "enums/CraterSize.h"
#include "MyTools.h"
#include <iostream>
#include <memory>
#include <cstring>

void Ground::Draw() const {
    ScreenSingleton::getInstance().SetColor(color);

    const size_t bufSize = width + 1;
    char* buf = new (std::nothrow) char[bufSize];
    if (buf == nullptr)
        return;

    if (vecCrates.size() == 0) {
        ScreenSingleton::getInstance().GotoXY(x, y);
        memset(buf, '=', bufSize);
        buf[bufSize - 1] = '\0';
        std::cout << buf;
    }
    else {
        const size_t X = size_t(x);
        char c;
        for (size_t i = X; i < width + X; i++)
        {
            c = (isInsideAnyCrater((double)i)) ? ' ' : '=';
            buf[i - X] = c;
        }

        ScreenSingleton::getInstance().GotoXY((double)X, y);
        buf[bufSize-1] = '\0';
        std::cout << buf;

        for (size_t i = 0; i < vecCrates.size(); i++)
        {
            vecCrates[i]->Draw();
        }
    }

    delete[] buf;
}

bool Ground::isInsideAnyCrater(double x) const {
    bool isInside = false;
    for (size_t i = 0; i < vecCrates.size(); i++) {
        if (vecCrates[i]->isInside(x)) {
            isInside = true;
            break;
        }
    }

    return isInside;
}

void Ground::AddCrater(double xn) {
    AbstractCrater* crater = CreateCrater();
    crater->SetPos(int(xn), y);
    vecCrates.push_back(crater);
}

AbstractCrater* CommonGround::CreateCrater() const {
    AbstractCrater* crater = new CommonCrater();
    return crater;
}

AbstractCrater* WinterGround::CreateCrater() const {
    AbstractCrater* crater = new WinterCrater();
    return crater;
}