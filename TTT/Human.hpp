#pragma once

#include "Player.hpp"

class Human : public Player {
public:
	Human(GameField::Value human);

	~Human();

	void playerMove(GameField& field) override;

	GameField::Value getSign() const override;

private:
	GameField::Value m_sign;
	std::string m_name;
};

