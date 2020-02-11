#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
    return cpu_;
}

bool compare(Process a, Process b) {return(a.CpuUtilization() >= b.CpuUtilization());}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    vector<int> pids;

    if (processes_.empty()) {
        pids = LinuxParser::Pids();
        processes_.resize(pids.size());
        for (unsigned int i=0; i<processes_.size(); i++) {
            processes_[i].SetPid(pids[i]);
            processes_[i].SetUid();
            processes_[i].SetCpuUtilization();
            processes_[i].SetUpTime();
            processes_[i].SetCommand();
            processes_[i].SetRam();
            processes_[i].SetUser();
        }
    }

    std::sort(processes_.begin(), processes_.end(), compare);
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    if (kernel.empty()) {
        kernel = LinuxParser::Kernel();
    }
    return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    if (operatingsystem.empty()) {
        operatingsystem = LinuxParser::OperatingSystem();
    }
    return operatingsystem;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
    return LinuxParser::UpTime();
}