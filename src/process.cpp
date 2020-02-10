#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() {
    return pid;
}

void Process::SetPid(int pid_) {
    pid = pid_;
}

void Process::SetUid() {
    uid = LinuxParser::Uid(pid);
}

void Process::SetUser() {
    user = LinuxParser::User(std::stoi(uid));
}

void Process::SetCpuUtilization(float cpuutilization_) {
    cpuutilization = cpuutilization_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    return cpuutilization;
}

void Process::SetCommand() {
    command = LinuxParser::Command(pid);
}

// TODO: Return the command that generated this process
string Process::Command() {
    return command;
}

void Process::SetRam() {
    ram = LinuxParser::Ram(pid);
    ram = std::to_string(std::stoi(ram) / 1000);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
    return ram;
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    return user;
}

void Process::SetUpTime(long uptime_) {
    uptime = uptime_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return uptime;
}

string Process::Uid() {
    return uid;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }