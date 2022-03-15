
#include <iostream>

#include "Tank.h"
#include "MyTools.h"
#include "ScreenSingleton.h"
#include "LevelGUI.h"

using namespace std;
using namespace MyTools;

const std::vector<std::string> Tank::message_box{{
                                                         "Go, complain to your mom that AI has made you cry!",
                                                         "Ha-ha, noob!",
                                                         "Omg! Learn how to play!",
                                                         "Pwned",
                                                         "I can beat you with my eyes closed!",
                                                         "Bring me an AA-gun!",
                                                         "Noob plane!"
                                                 }
};

void Controller::push_msg(uint16_t x, uint16_t y, std::string_view&& str) {
    gui->AddMessage(x, y, str);
}

bool Tank::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void Tank::Draw()
{
	ScreenSingleton::getInstance().SetColor(CC_Cyan);
	ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x-2, y - 2);
	cout << "#######   #";
	ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x,y);
	cout << " ###########";

    if (dice(10) == 0)
        controller->push_msg(x - 4, y - 5, GetRandomString());
}

void Tank::SetController(Controller* _controller) {
    controller = _controller;
}

std::string Tank::GetRandomString() const {
    return message_box[dice(message_box.size())];
}

uint16_t Tank::dice(uint16_t upper) const {
    std::random_device rng;
    std::mt19937_64 mt { rng() };
    return static_cast<uint16_t> (mt() % upper + 0);
}