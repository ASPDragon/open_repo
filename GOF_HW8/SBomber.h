#pragma once

#include <vector>
#include <iostream>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    void OneMoreBomb();
    void OneMoreDestroyableObject2();
    void AnimateScrolling();

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void CheckDestoyableObjects(Bomb* pBomb);

    void DeleteDynamicObj(DynamicObject * pBomb);
    void DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

      static std::size_t constexpr kScrollHeight = 30;
  static std::size_t constexpr kScrollWidth = 30;
  inline static char const kScrollData[kScrollHeight][kScrollWidth] = {
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "  Project manager:        	",
    " 	 Ivan Vasilevich      	",
    "                          	",
    "  Developers:             	",
    " 	 Nikolay Gavrilov     	",
    " 	 Dmitriy Sidelnikov   	",
    " 	 Eva Brown            	",
    "                          	",
    "  Designers:              	",
    " 	 Anna Pachenkova      	",
    " 	 Elena Shvaiber       	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	",
    "                          	"
  };
};