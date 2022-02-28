#include "SBomber.h"
#include "MyTools.h"
#include "ScreenSingleton.h"

#if defined(_WIN32) || defined(WIN32)

#include <conio.h>
#include <iostream>

#else

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#endif


int main(void) {
    try {
        FileLogger logger("log.txt");

        SBomber game(&logger);

        do {
            game.TimeStart();

            if (kbhit()) {
                game.ProcessKBHit();
            }

            ScreenSingleton::getInstance().ClrScr();

            game.DrawFrame();
            game.MoveObjects();
            game.CheckObjects();

            game.TimeFinish();

        } while (!game.GetExitFlag());
    }

    catch(std::runtime_error& reading_failure) {
        std::cerr << "Error: " << reading_failure.what() << '\n';
    }
    return 0;
}
