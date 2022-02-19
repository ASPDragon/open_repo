#pragma once

#include <stdint.h>
#include <string>
#include <queue>


#include "GameObject.h"

class LevelGUI : public GameObject {
public:

    LevelGUI() : bombsNumber{ 0 }, score{ 0 }, passedTime{ 0 }, fps{ 0 }, height{ 0 }, time{ 0 } { }

    void  SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    void  SetHeight(uint16_t heightN) { height = heightN; };
    
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() override;

    void AddMessage(uint16_t x, uint16_t y, std::string_view message);

private:
    bool CheckTimer();

    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;
    uint16_t time;

    struct Message {
        uint16_t x, y;
        std::string text;
    };

    std::queue<Message> message_collection;
};



