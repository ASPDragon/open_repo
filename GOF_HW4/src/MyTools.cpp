#include "MyTools.h"

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

// // FileLoggerSingleton friend function
IFileLogger& GetInternalInstance() {
    static FileLoggerSingleton theInstance;
    return theInstance;
}

// FileLoggerSingleton methods
FileLoggerSingleton::~FileLoggerSingleton() {
    CloseLogFile();
}

void FileLoggerSingleton::OpenLogFile(const std::string &FN) { logOut.open(FN, std::ios_base::out); }

void FileLoggerSingleton::CloseLogFile() {
    if (logOut.is_open()) {
        logOut.close();
    }
}

std::string GetCurDateTime() {
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char* buf = ctime(&time);
    return std::string(buf);
}

void FileLoggerSingleton::WriteToLog(const std::string &str) {
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << std::endl;
    }
}

void FileLoggerSingleton::WriteToLog(const std::string &str, int n) {
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << n << std::endl;
    }
}

void FileLoggerSingleton::WriteToLog(const std::string &str, double d) {
    if (logOut.is_open()) {
        logOut << GetCurDateTime() << " - " << str << d << std::endl;
    }
}

IFileLogger& FileLoggerSingleton::getInstance() {
    return FileLoggerSingletonProxy::getInstance();
}

// FileLoggerSingletonProxy methods
IFileLogger& FileLoggerSingletonProxy::getInstance() {
    static FileLoggerSingletonProxy theInstance;
    return theInstance;
}

void FileLoggerSingletonProxy::OpenLogFile(const std::string &FN) {
    t.start("Open operation timer");
    GetInternalInstance().OpenLogFile(FN);
    TimerSingleton::getInstance().SetOpsElapsed(std::move(t.msPassed()), std::string(__func__));
}

void FileLoggerSingletonProxy::CloseLogFile() {
    t.start("Close operation timer");
    GetInternalInstance().CloseLogFile();
    TimerSingleton::getInstance().SetOpsElapsed(std::move(t.msPassed()), std::string(__func__));
}

void FileLoggerSingletonProxy::WriteToLog(const std::string &str) {
    t.start("Write operation timer");
    GetInternalInstance().WriteToLog(str);
    TimerSingleton::getInstance().SetOpsElapsed(std::move(t.msPassed()), std::string(__func__));
}

void FileLoggerSingletonProxy::WriteToLog(const std::string &str, int n) {
    t.start("Write Int operation timer");
    GetInternalInstance().WriteToLog(str, n);
    TimerSingleton::getInstance().SetOpsElapsed(std::move(t.msPassed()),
                                                std::string(__func__) + " int");
}

void FileLoggerSingletonProxy::WriteToLog(const std::string &str, double d) {
    t.start("Write Double operation timer");
    GetInternalInstance().WriteToLog(str, d);
    TimerSingleton::getInstance().SetOpsElapsed(std::move(t.msPassed()),
                                                std::string(__func__) + " double");
}

// TimerSingleton methods
TimerSingleton& TimerSingleton::getInstance() {
    static TimerSingleton theInstance;
    return theInstance;
}

void TimerSingleton::SetOpsElapsed(uint16_t &&time, const std::string &key) {
    ++stat[key].first;
    stat[key].second += time;
}