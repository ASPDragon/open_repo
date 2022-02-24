#include "MyTools.h"

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

void FileLogger::OpenLogFile(const std::string &FN) { logOut.open(FN, std::ios_base::out); }

void FileLogger::CloseLogFile() {
  if (logOut.is_open()) {
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
