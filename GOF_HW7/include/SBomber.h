#pragma once

#include <vector>
#include <memory>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class FileLogger;
class SBomberImpl;

class SBomber {
public:
    explicit SBomber(FileLogger* logger);
    ~SBomber();
    
    bool GetExitFlag() const;

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    std::unique_ptr<SBomberImpl> impl;
};