#pragma once

#include <random>
#include "Player.hpp"

class AI : public Player {
public:
	AI(GameField::Value AI, GameField::Value opponent);

	~AI() {};

	void playerMove(GameField& field) override;

	bool aiWinChk(GameField& field);

	bool humWinChk(GameField& field);

	GameField::Value getSign() const override;

private:
	GameField::Value m_sign;
	GameField::Value m_opponent;
	std::string m_name;
};