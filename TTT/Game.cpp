#include "Game.hpp"

Game::Game() {
	ticTacToe();
}

Game::~Game() {};

void Game::setGameMode() {
	std::cout << "Please, input integers for game field sides (horizontal and vertical), using space: ";
	std::cin >> m_hor >> m_vert;
	m_towin = std::min(m_hor, m_vert);
}

void Game::setSides(GameField::Value valP1) {
	valP1 == GameField::Value::CROSS ? m_player2 = GameField::Value::ZERO : m_player2 = GameField::Value::CROSS;
	m_player1 = valP1;
}

void Game::swapSides() {
	(m_player1 == GameField::Value::CROSS) ? setSides(GameField::Value::ZERO) : setSides(GameField::Value::CROSS);
	m_player1MovesFirst = !m_player1MovesFirst;
}

void Game::playerSide() {
	do {
		std::cout << "Please, choice your side (x/o): ";
		std::cin >> m_player1Side;
		std::transform(m_player1Side.begin(), m_player1Side.end(), m_player1Side.begin(), ::tolower);
	} while (!(m_player1Side.find('x') || m_player1Side.find('o')));
	std::cout << std::endl;

	(m_player1Side == "x") ? setSides(GameField::Value::CROSS) : setSides(GameField::Value::ZERO);
	if (m_player1 == GameField::Value::CROSS)
		m_player1MovesFirst = true;
	else
		m_player1MovesFirst = false;
}

bool Game::gameCheck(GameField& field, const Player& player) {
	if (field.winCheck(player.getSign())) {
		std::cout << std::endl;
		return true;
	}
	if (isDraw(field)) {
		std::cout << "Draw!" << std::endl;
		return true;
	}
	return false;
}

bool Game::isDraw(GameField& field) {
	for (int y{ 0 }; y < field.height(); ++y)
		for (int x{ 0 }; x < field.width(); ++x)
			if (field.isEmpty(y, x))
				return false;
	return true;
}

void Game::ticTacToe() {
	setGameMode();
	playerSide();

	while (true) {
		GameField field(m_vert, m_hor, m_towin);
		field.print();
		Human playerOne(m_player1);
		AI playerTwo(m_player2, m_player1);
		std::unique_ptr<Player> player1Pointer{ &playerOne };
		std::unique_ptr<Player> player2Pointer{ &playerTwo };
		auto current_player = m_player1MovesFirst == true ? move(player1Pointer) : move(player2Pointer);
		
		while (true) {
			current_player->playerMove(field);
			field.print();
			if (gameCheck(field, *current_player)) break;
			current_player == player1Pointer ? std::swap(player2Pointer, current_player) : std::swap(player1Pointer, current_player);
		}
		std::string answer;
		std::cout << "One more round? ";
		std::cin >> answer;
		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer.find('y')) {
			std::cout << "I never planned to play with you in the first place" << std::endl;
			break;
		}
		swapSides();
	}
}