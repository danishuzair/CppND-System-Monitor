#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  float CalculateProcessUtilization(std::vector<std::string> data);
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string operatingsystem;
  std::string kernel;
  const float hertz = float(sysconf(_SC_CLK_TCK));
};

#endif