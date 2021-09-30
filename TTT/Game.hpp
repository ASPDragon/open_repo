#pragma once

#include <memory>
#include "AI.hpp"
#include "Human.hpp"

class Game {
public:
	Game();

	~Game();

	void setGameMode();

	void setSides(GameField::Value valP1);

	void swapSides();

	void playerSide();

	bool gameCheck(GameField& field, const Player& player);

	bool isDraw(GameField& field);

	Player& getNextPlayer(Player& current_player);

	void ticTacToe();

private:
	int m_vert;
	int m_hor;
	int m_towin;
	std::string m_player1Side;
	GameField::Value m_player1;
	GameField::Value m_player2;
	bool m_player1MovesFirst;
};

