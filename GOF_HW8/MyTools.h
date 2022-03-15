#pragma once

#include <stdint.h>
#include <string>
#include <random>

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================

	void __fastcall OpenLogFile(const std::string& FN);

	void CloseLogFile();

	void __fastcall WriteToLog(const std::string& str);

	void __fastcall WriteToLog(const std::string& str, int n);

	void __fastcall WriteToLog(const std::string& str, double d);

	//=============================================================================================

};

class Random {
private:
    using int_r = std::uniform_int_distribution<std::size_t>;
    using double_r = std::uniform_real_distribution<double>;
    std::random_device rd;
    std::mt19937 gen;
    int_r int_dist;
    double_r double_dist;

public:
    explicit Random();
    explicit Random(std::size_t const from, std::size_t const to);
    explicit Random(double const from, double const to);
    void Interval(std::size_t const from, std::size_t const to);
    void Interval(double const from, double const to);
    std::size_t Integer();
    double Real();
};

// double compare
class DoubleCompare {
public:
    static bool IsEqual(double const x, double const y);
    static bool IsMoreOrEqual(double const x, double const y);
    static bool IsLessOrEqual(double const x, double const y);
};