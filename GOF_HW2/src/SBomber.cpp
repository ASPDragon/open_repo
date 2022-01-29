
#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "ScreenSingleton.h"
#include "enums/CraterSize.h"
#include <chrono>
#include <thread>

SBomber::SBomber()
  : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0),
    fps(0), bombsNumber(10), score(0) {
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");


    Plane *p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    LevelGUI *pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    Ground *pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    Tank *pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    House *pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber() {
  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    if (vecDynamicObj[i] != nullptr) {
      delete vecDynamicObj[i];
    }
  }

  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    if (vecStaticObj[i] != nullptr) {
      delete vecStaticObj[i];
    }
  }
}

void SBomber::MoveObjects() {
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects() {
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI() {
  if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
    exitFlag = true;
  }
}

void SBomber::CheckBombsAndGround() {
  std::vector<IBomb*> vecBombs = FindAllBombs();
  Ground* pGround = FindGround();
  const double y = pGround->GetY();
  for (size_t i = 0; i < vecBombs.size(); i++) {
    if (vecBombs[i]->GetY() >= y) {
      pGround->AddCrater(vecBombs[i]->GetX());
      CheckDestoyableObjects(vecBombs[i]);
      auto DeleteDynamicObj =
              std::make_shared<DeleteObject<DynamicObject>>(vecDynamicObj, vecBombs[i]);
      CommandExecuter(DeleteDynamicObj.get());
    }
  }
}

void SBomber::CheckDestoyableObjects(IBomb* pBomb) {
  std::vector<DestroyableGroundObject*> vecDestoyableObjects =
      FindDestoyableGroundObjects();
  const double size = pBomb->GetWidth();
  const double size_2 = size / 2;
  for (size_t i = 0; i < vecDestoyableObjects.size(); i++) {
    const double x1 = pBomb->GetX() - size_2;
    const double x2 = x1 + size;
    if (vecDestoyableObjects[i]->isInside(x1, x2)) {
      score += vecDestoyableObjects[i]->GetScore();
        auto DeleteStaticObj =
                std::make_shared<DeleteObject<GameObject>>(vecStaticObj, vecDestoyableObjects[i]);
        CommandExecuter(DeleteStaticObj.get());
    }
  }
}

void SBomber::CommandExecuter(ICommand * pCommand) {
    pCommand->Execute();
}

std::vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const {
  std::vector<DestroyableGroundObject*> vec;
  Tank* pTank;
  House* pHouse;
  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
    if (pTank != nullptr) {
      vec.push_back(pTank);
      continue;
    }

    pHouse = dynamic_cast<House*>(vecStaticObj[i]);
    if (pHouse != nullptr) {
      vec.push_back(pHouse);
      continue;
    }
  }

  return vec;
}

Ground* SBomber::FindGround() const {
  Ground* pGround;

  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
    if (pGround != nullptr) {
      return pGround;
    }
  }

  return nullptr;
}

std::vector<IBomb*> SBomber::FindAllBombs() const {
  std::vector<IBomb*> vecBombs;

  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    IBomb* pBomb = dynamic_cast<IBomb*>(vecDynamicObj[i]);
    if (pBomb != nullptr) {
      vecBombs.push_back(pBomb);
    }
  }

  return vecBombs;
}

Plane* SBomber::FindPlane() const {
  for (size_t i = 0; i < vecDynamicObj.size(); i++) {
    Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
    if (p != nullptr) {
      return p;
    }
  }

  return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const {
  for (size_t i = 0; i < vecStaticObj.size(); i++) {
    LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
    if (p != nullptr) {
      return p;
    }
  }

  return nullptr;
}

void SBomber::ProcessKBHit() {
    int c = getchar();

    if (c == 224) {
        c = getchar();
    }

    Plane* plane = FindPlane();

    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked. key = ", c);

    constexpr uint16_t freefall = 2;

    switch (c) {

        case 27: // esc
            exitFlag = true;
            break;

        case 72: // up
            FindPlane()->ChangePlaneY(-0.25);
            break;

        case 80: // down
            FindPlane()->ChangePlaneY(0.25);
            break;

        case 'b': {
            std::unique_ptr<BombLauncher> drop = std::make_unique<DropBomb>
                    (plane, vecDynamicObj, bombsNumber, freefall, (uint16_t) SMALL_CRATER_SIZE, score);
            CommandExecuter(drop.get());
            bombsNumber--;
            break;
        }

        case 'B': {
            std::unique_ptr<BombLauncher> dropdecor = std::make_unique<DropDecoratedBomb>
                    (plane, vecDynamicObj, bombsNumber, freefall, SMALL_CRATER_SIZE, score);
            CommandExecuter(dropdecor.release());
            bombsNumber--;
            break;
        }


        default:
            break;
    }
}

void SBomber::DrawFrame() {
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++) {
        if (vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++) {
        if (vecStaticObj[i] != nullptr) {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart() {
    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " was invoked");
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void SBomber::TimeFinish() {
    finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    FileLoggerSingletonProxy::getInstance().WriteToLog(std::string(__func__) + " deltaTime = ", (int) deltaTime);
}
