#include "Bomb.h"
#include <iostream>
#include "ScreenSingleton.h"

void Bomb::Draw() const {
  //ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
  ScreenSingleton::getInstance().GotoXY(x, y);
  std::cout << "*";
}

BombDecorator::BombDecorator(IBomb* bomb)
        : bomb(bomb) {}

void BombDecorator::Move(uint16_t time)
{
    bomb->Move(time * 1.6);
}

void BombDecorator::Draw() const
{
    bomb->Draw();
    // Некоторое изменение внешнего вида бомбы
    ScreenSingleton::getInstance().GotoXY(bomb->GetX(), bomb->GetY() - 1);
    std::cout << "|";
}

void BombDecorator::SetPos(double nx, double ny) {
    bomb->SetPos(nx, ny);
}

uint16_t BombDecorator::GetWidth() const {
    return bomb->GetWidth();
}