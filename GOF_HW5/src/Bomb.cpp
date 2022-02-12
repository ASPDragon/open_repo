#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"
#include "DestroyableGroundObject.h"

DestroyableGroundObject* Bomb::CheckDestroyableObjects() {
    const double size = this->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecObserver.size(); ++i) {
        const double x1 = this->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecObserver[i]->HandleInsideCheck(x1, x2)) {
            return vecObserver[i];
        }
    }
    return nullptr;
}

void Bomb::Draw() const {
  //ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

void Bomb::Accept(const Visitor& v) {
    v.log(*this);
}