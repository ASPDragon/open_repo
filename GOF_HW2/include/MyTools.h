#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include "Timer.hpp"

class IFileLogger {
public:
    virtual ~IFileLogger() = default;

    virtual void OpenLogFile(const std::string& FN) = 0;
    virtual void CloseLogFile() = 0;

    virtual void WriteToLog(const std::string& str) = 0;
    virtual void WriteToLog(const std::string& str, int n) = 0;
    virtual void WriteToLog(const std::string& str, double d) = 0;
};

class FileLoggerSingleton : public IFileLogger {
public:
    static IFileLogger& getInstance();

    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;

    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;

private:
    std::ofstream logOut;

    FileLoggerSingleton() = default;
    ~FileLoggerSingleton();

    friend IFileLogger& GetInternalInstance();

    FileLoggerSingleton(FileLoggerSingleton& root) = delete;
    FileLoggerSingleton(FileLoggerSingleton&& root) = delete;

    FileLoggerSingleton& operator= (const FileLoggerSingleton&) = delete;
    FileLoggerSingleton& operator= (FileLoggerSingleton&&) = delete;
};

class FileLoggerSingletonProxy : public IFileLogger {
public:
    static IFileLogger& getInstance();

    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;

    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;

private:
    FileLoggerSingletonProxy() = default;
    ~FileLoggerSingletonProxy() = default;

    Timer t;

    FileLoggerSingletonProxy(FileLoggerSingletonProxy& root) = delete;
    FileLoggerSingletonProxy(FileLoggerSingletonProxy&& root) = delete;

    FileLoggerSingletonProxy& operator= (const FileLoggerSingletonProxy&) = delete;
    FileLoggerSingletonProxy& operator= (FileLoggerSingletonProxy&&) = delete;
};

class TimerSingleton {
public:
    static TimerSingleton& getInstance();
    void SetOpsElapsed(uint16_t&& time, std::string const& key);
    std::unordered_map<std::string, std::pair<int, double>> GetMap() { return stat; }

private:
    TimerSingleton() = default;
    ~TimerSingleton() = default;

    std::unordered_map<std::string, std::pair<int, double>> stat;

    TimerSingleton(TimerSingleton& root) = delete;
    TimerSingleton(TimerSingleton&& root) = delete;

    TimerSingleton& operator= (const TimerSingleton&) = delete;
    TimerSingleton& operator= (TimerSingleton&&) = delete;
};