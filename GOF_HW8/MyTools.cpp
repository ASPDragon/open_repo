
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    ofstream logOut;

    //=============================================================================================

    void ClrScr()
    {
        system("cls");
    }

    void GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================

    void OpenLogFile(const string& FN)
    {
        logOut.open(FN, ios_base::out);
    }

    void CloseLogFile()
    {
        if (logOut.is_open())
        {
            logOut.close();
        }
    }

    string GetCurDateTime()
    {
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    }

    void WriteToLog(const string& str)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void __fastcall WriteToLog(const string& str, int n)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void __fastcall WriteToLog(const string& str, double d)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

    //=============================================================================================


} // namespace MyTools

Random::Random() {
    gen.seed(rd());
}

Random::Random(const std::size_t from, const std::size_t to) {
    gen.seed(rd());
    int_dist.param(int_r::param_type(from, to));
}

Random::Random(const double from, const double to) {
    gen.seed(rd());
    double_dist.param(double_r::param_type(from, to));
}

void Random::Interval(const std::size_t from, const std::size_t to) {
    int_dist.param(int_r::param_type(from, to));
}

void Random::Interval(const double from, const double to) {
    double_dist.param(double_r::param_type(from, to));
}

std::size_t Random::Integer() {
    return int_dist(gen);
}

double Random::Real() {
    return double_dist(gen);
}


// double compare implementation
bool DoubleCompare::IsEqual(double const x, double const y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

bool DoubleCompare::IsMoreOrEqual(double const x, double const y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon() || x > y;
}

bool DoubleCompare::IsLessOrEqual(double const x, double const y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon() || x < y;
}