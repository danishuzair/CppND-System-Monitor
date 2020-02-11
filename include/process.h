#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  void SetPid(int pid_);
  void SetUid();
  void SetUser();
  void SetCpuUtilization();
  std::string User();                      // TODO: See src/process.cpp
  void SetCommand();
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  void SetRam();
  std::string Ram();                       // TODO: See src/process.cpp
  void SetUpTime ();
  long int UpTime();                       // TODO: See src/process.cpp
//  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  std::string Uid();

  // TODO: Declare any necessary private members
 private:
    int pid;
    std::string uid, user, command, ram;
    float cpuutilization;
    long int uptime;
};

#endif