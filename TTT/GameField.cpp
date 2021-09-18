#include "GameField.hpp"

GameField::GameField(int szY, int szX, int towin)
: m_szY(szY), m_szX(szX), m_towin(towin) {
	field.resize(m_szY * m_szX);
	for (auto& x : field)
		x = Value::EMPTY;
};

void GameField::print() {
	std::system("cls");
	for (int i = 0; i < m_szX * 2 + 1; ++i)
		std::cout << '-';
	std::cout << std::endl;
	for (int y{ 0 }; y < m_szY; ++y) {
		std::cout << '|';
		for (int x{ 0 }; x < m_szX; ++x) {
			std::cout << static_cast<char>(getValue(y, x)) << '|';
		}
		std::cout << std::endl;
	}
	for (int j = 0; j < m_szX * 2 + 1; ++j)
		std::cout << '-';
	std::cout << std::endl;
}

void GameField::setValue(int y, int x, Value value) {
	field[y * m_szX + x] = value;
}

GameField::Value GameField::getValue(int y, int x) const {
	return field[y * m_szX + x];
}

bool GameField::winCheck(Value player) {
	for (int y{ 0 }; y < height(); ++y) {
		for (int x{ 0 }; x < width(); ++x) {
			if (lineCheck(y, x, 1, 0, winSeq(), player)) return true; // vert
			if (lineCheck(y, x, 1, 1, winSeq(), player)) return true; // diag1
			if (lineCheck(y, x, 0, 1, winSeq(), player)) return true; // hor
			if (lineCheck(y, x, 1, -1, winSeq(), player)) return true; // diag2
		}
	}
	return false;
}

bool GameField::lineCheck(int y, int x, int vy, int vx, int len, Value player) {
	const int endy{ y + (len - 1) * vy };
	const int endx{ x + (len - 1) * vx };

	if (!isValid(endy, endx))
		return false;
	for (int i{ 0 }; i < len; ++i)
		if (getValue((y + i * vy), (x + i * vx)) != player)
			return false;
	return true;
}

bool GameField::isEmpty(int row, int col) {
	return getValue(row, col) == Value::EMPTY;
}

bool GameField::isValid(int y, int x) {
	return (y >= 0 && y < m_szY) && (x >= 0 && x < m_szX);
}