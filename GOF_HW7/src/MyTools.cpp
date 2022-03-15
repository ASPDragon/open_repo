#include "MyTools.h"

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

FileLogger::FileLogger(const std::string& filename) {
    logOut.open(filename);

    if (logOut.is_open())
        logOut << GetCurDateTime() << " - has begun" << std::endl;
    else
        throw std::runtime_error("Reading failure");
}

FileLogger::~FileLogger() {
    if(logOut.is_open()) {
        logOut << GetCurDateTime() << " - has done" << std::endl;
        logOut.close();
    }
}

std::string FileLogger::GetCurDateTime() {
  auto cur = std::chrono::system_clock::now();
  time_t time = std::chrono::system_clock::to_time_t(cur);
  char* buf = ctime(&time);
  return std::string(buf);
}

void FileLogger::WriteToLog(const std::string &str) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << std::endl;
  }
}

void FileLogger::WriteToLog(const std::string &str, int n) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << n << std::endl;
  }
}

void FileLogger::WriteToLog(const std::string &str, double d) {
  if (logOut.is_open()) {
    logOut << GetCurDateTime() << " - " << str << d << std::endl;
  }
}
