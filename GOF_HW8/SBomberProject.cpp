
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    MyTools::OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    game.AnimateScrolling();

    std::cout << std::endl;
    MyTools::ClrScr();
//    MyTools::SetColor(CC_White);

    MyTools::CloseLogFile();

    return 0;
}
