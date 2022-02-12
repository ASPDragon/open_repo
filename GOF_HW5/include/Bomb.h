#pragma once

#include <vector>
#include <memory>
#include "DynamicObject.h"

class DestroyableGroundObject;

class Bomb : public DynamicObject
{
public:
    void AddObserver(DestroyableGroundObject* obj) {
        vecObserver.push_back(obj);
    }

    DestroyableGroundObject* CheckDestroyableObjects();

	static const uint16_t BombCost = 10; // ��������� ����� � �����
    void Accept(const Visitor& v);

	void Draw() const override;

private:
    std::vector<DestroyableGroundObject*> vecObserver;
};