#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <random>

#include "DestroyableGroundObject.h"

class LevelGUI;

class Controller {
public:
    Controller(LevelGUI* gui) : gui{ gui } {}
    void push_msg(uint16_t x, uint16_t y, std::string_view&& str);
private:
    LevelGUI* gui;
};

class Tank : public DestroyableGroundObject {
public:

	bool  isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() override;

    void SetController(Controller* _controller);

private:
    std::string GetRandomString() const;
    uint16_t dice(uint16_t upper) const;

    const static std::vector<std::string> message_box;
    Controller* controller;
	const uint16_t score = 30;
};

