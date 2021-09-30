#include "Human.hpp"

Human::Human(GameField::Value sign)
	: m_sign(sign), m_name("Player") {};

Human::~Human() {};

void Human::playerMove(GameField& field) {
	int y, x;

	do {
		std::cout << "Please, input coordinates of X and Y (1 - " << field.winSeq() << "), using space: ";
		std::cin >> x >> y;
		x--; y--;
	} while (!field.isValid(y, x) || !field.isEmpty(y, x));
	field.setValue(y, x, m_sign);
}

GameField::Value Human::getSign() const {
	return m_sign;
}