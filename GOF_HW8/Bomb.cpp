
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::SetColor(CC_LightMagenta);
    GotoXY(x, y);
    cout << "*";
}

DynamicObject* Bomb::clone() {
    DynamicObject* b = new Bomb(*this);
    b->SetPos(x + 5, y);
    return b;
}