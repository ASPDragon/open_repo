#include "AI.hpp"

AI::AI(GameField::Value sign, GameField::Value opponent)
	: m_sign(sign), m_opponent(opponent), m_name("AI") {};

void AI::playerMove(GameField& field) {
	int y, x;
	if (aiWinChk(field)) return;
	if (humWinChk(field)) return;

	std::random_device random;
	std::mt19937_64 mt(random());
	std::uniform_real_distribution<double> dist(0, field.winSeq());

	do {
		y = dist(mt);
		x = dist(mt);
	} while (!field.isEmpty(y, x));
	field.setValue(y, x, m_sign);
}

bool AI::aiWinChk(GameField& field) {
	for (int y{ 0 }; y < field.height(); ++y) {
		for (int x{ 0 }; x < field.width(); ++x) {
			if (field.isEmpty(y, x)) {
				field.setValue(y, x, m_sign);
				if (field.winCheck(m_sign))
					return true;
				field.setValue(y, x, GameField::Value::EMPTY);
			}
		}
	}
	return false;
}

bool AI::humWinChk(GameField& field) {
	for (int y{ 0 }; y < field.height(); ++y) {
		for (int x{ 0 }; x < field.width(); ++x) {
			if (field.isEmpty(y, x)) {
				field.setValue(y, x, m_opponent);
				if (field.winCheck(m_opponent)) {
					field.setValue(y, x, m_sign);
					return true;
				}
				field.setValue(y, x, GameField::Value::EMPTY);
			}
		}
	}
	return false;
}

GameField::Value AI::getSign() const {
	return m_sign;
}