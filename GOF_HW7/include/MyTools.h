#pragma once

#include <string>
#include <fstream>

class FileLogger {
public:
    FileLogger(const std::string& filename);

    ~FileLogger();

    std::string GetCurDateTime();

    void WriteToLog(const std::string &str);
    void WriteToLog(const std::string &str, int n);
    void WriteToLog(const std::string &str, double d);

private:
    std::ofstream logOut;
};
