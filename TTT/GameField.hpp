#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class GameField {
public:
	GameField(int, int, int);

	enum class Value { CROSS = 'X', ZERO = 'O', EMPTY = ' ' };

	void print();

	void setValue(int y, int x, Value value);

	Value getValue(int y, int x) const;

	bool winCheck(GameField::Value player);

	bool lineCheck(int y, int x, int vy, int vx, int len, GameField::Value player);

	bool isEmpty(int row, int col);

	bool isValid(int y, int x);

	int height() const { return m_szY; }

	int width() const { return m_szX; }

	int winSeq() const { return m_towin; }

	~GameField() {};

private:
	Value m_value;
	int m_szY;
	int m_szX;
	int m_towin;
	std::vector<Value> field;
};