#pragma once

#include "GameField.hpp"

class Player {
public:
	virtual void playerMove(GameField& field) = 0;

	virtual GameField::Value getSign() const = 0;
};