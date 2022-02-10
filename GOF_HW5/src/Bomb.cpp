#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"

void Bomb::CheckDestoyableObjects(Bomb* pBomb) {
    std::vector<DestroyableGroundObject*> vecDestoyableObjects =
            FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2)) {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void Bomb::Draw() const {
  //ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

void Bomb::Accept(const Visitor& v) {
    v.log(*this);
}