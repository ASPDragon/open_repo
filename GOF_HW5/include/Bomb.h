#pragma once

#include "DynamicObject.h"

class Observer {
public:
    virtual ~Observer();

protected:
    Observer() = default;
};

class Bomb : public DynamicObject
{
public:
    void  CheckDestoyableObjects();

	static const uint16_t BombCost = 10; // ��������� ����� � �����
    void Accept(const Visitor& v);

	void Draw() const override;

private:

};

