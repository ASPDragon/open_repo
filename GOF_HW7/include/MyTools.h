#pragma once

#include <string>
#include <fstream>

class FileLogger {
public:
    FileLogger(const std::string& filename) {
        file.open(filename);
    }

    ~FileLogger() {
        file.close();
    }

    void OpenLogFile(const std::string &FN);
    void CloseLogFile();

    std::string GetCurDateTime();

    void WriteToLog(const std::string &str);
    void WriteToLog(const std::string &str, int n);
    void WriteToLog(const std::string &str, double d);

private:
    std::ifstream file;
    std::ofstream logOut;
};
