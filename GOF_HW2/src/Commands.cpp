//
// Created by ionian_caster on 2022-01-25.
//

#include "Commands.h"
#include "MyTools.h"
#include <cassert>

BombLauncher::BombLauncher(const Plane* _plane, std::vector<DynamicObject*>& _ObjectsVec, const uint16_t& _bombsQuantity,
         const uint16_t& _freeFallSpeed, const uint16_t& _craterWidth, int16_t& _score)
         : plane{_plane}, ObjectsVec{_ObjectsVec}, bombsQuantity{_bombsQuantity}, freeFallSpeed{_freeFallSpeed},
         craterWidth{_craterWidth}, score{_score} {};

IBomb* BombLauncher::BombCreator() const {
    IBomb* pBomb = new Bomb();
    assert(bombsQuantity > 0);
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");

    double x = plane->GetX() + 4;
    double y = plane->GetY() + 2;

    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(freeFallSpeed);
    pBomb->SetPos(x, y);
    pBomb->SetWidth(craterWidth);
    return pBomb;
}

void DropBomb::Execute() {
        ObjectsVec.push_back(BombCreator());
        score -= Bomb::BombCost;
}

void DropDecoratedBomb::Execute() {
    auto pBomb = std::make_unique<BombDecorator>(BombCreator());
    ObjectsVec.push_back(pBomb.release());
    score -= Bomb::BombCost;
}