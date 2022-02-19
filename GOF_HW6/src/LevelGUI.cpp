#include "LevelGUI.h"
#include <iostream>
#include "MyTools.h"
#include "ScreenSingleton.h"
#include <cstring>
#include <random>

void LevelGUI::Draw() {
    ScreenSingleton::getInstance().SetColor(CC_White);

    ScreenSingleton::getInstance().GotoXY(x, y);
    char* buf = new (std::nothrow) char[width + 1];
    if (buf == nullptr) {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    std::cout << buf;
    ScreenSingleton::getInstance().GotoXY(x, y + height);
    std::cout << buf;
    delete [] buf;
    buf = nullptr;
    
    for (size_t i = size_t(y); i < height + y; i++) {
        ScreenSingleton::getInstance().GotoXY(x, (double)i);
        std::cout << "+";
        ScreenSingleton::getInstance().GotoXY(x + width - 1, (double)i);
        std::cout << "+";
    }

    ScreenSingleton::getInstance().GotoXY(3, 1);
    std::cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    ScreenSingleton::getInstance().GotoXY(25, 1);
    std::cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    ScreenSingleton::getInstance().GotoXY(46, 1);
    std::cout << "BombsNum: " << bombsNumber;
    ScreenSingleton::getInstance().GotoXY(62, 1);
    std::cout << "Score: " << score;

    if (!message_collection.empty()) {
        ScreenSingleton::getInstance().GotoXY(message_collection.front().x, message_collection.front().y);
        ScreenSingleton::getInstance().SetColor(CC_Red);
        std::cout << message_collection.front().text;

        if(CheckTimer())
            message_collection.pop();
    }
}

void  LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew) {
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}

void LevelGUI::AddMessage(uint16_t x, uint16_t y, std::string_view message) {
    message_collection.push(Message{x, y, std::string{message}});
}

bool LevelGUI::CheckTimer() {
    if(time == 0) {
        time = static_cast<int>(passedTime / 1000.0);
        return false;
    }
    else if((static_cast<int>(passedTime / 1000.0) - time) >= 2){
        time = 0;
        return true;
    }
    else {
        return false;
    }
}