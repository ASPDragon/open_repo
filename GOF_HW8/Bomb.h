#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:
	Bomb() = default;

	Bomb(const Bomb& obj) {
		x = obj.x;
		y = obj.y;
		width = obj.width;
	}

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;
	DynamicObject* clone();

private:

};

