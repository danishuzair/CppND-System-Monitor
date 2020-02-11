#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return string();
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    float memoryutilization;
    std::string key, kB;
    int memory, memorytotal=1, memoryfree=0;
    string line;
    std::ifstream stream(kProcDirectory + kMeminfoFilename);
    if(stream.is_open()) {
        while(std::getline(stream,line)) {
            std::istringstream linestream(line);
            while (linestream>>key>>memory>>kB) {
                if (key == "MemTotal:") {
                    memorytotal = memory;
                }
                else if (key == "MemFree:") {
                    memoryfree = memory;
                    break;
                }
            }
        }
    }
    memoryutilization = float(memorytotal - memoryfree) / float(memorytotal);
    return memoryutilization;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    long uptime = 0, value1 = 0, value2 = 0, value3 = 0;
    string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> value1 >> value2 >> value3;
    }
    uptime = value1; // + value3;
    return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
float LinuxParser::ProcessUtilization(int pid) {
    string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    string s11, s12, s13, s14, s15, s16, s17, s18, s19, s20;
    string s21, s22;
    string line;
    std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream>>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12>>s13>>s14>>s15>>s16>>s17>>s18>>s19>>s20>>s21>>s22;
            break;
        }
    }

    float hertz = float(sysconf(_SC_CLK_TCK));
    float total_time = float(UpTime(pid)) + (std::stof(s15) + std::stof(s16) + std::stof(s17))/hertz;
    float seconds = float(UpTime()) - (std::stof(s22)/ hertz);
    float processutilization = (total_time / seconds);
    return processutilization;
}

std::vector<std::string> LinuxParser::CpuUtilization() {
    std::vector<std::string> cpuutilization;
    string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, key;
    string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while(std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10;
            if (key == "cpu") {
                break;
            }
        }
    }
    cpuutilization.push_back(s1);
    cpuutilization.push_back(s2);
    cpuutilization.push_back(s3);
    cpuutilization.push_back(s4);
    cpuutilization.push_back(s5);
    cpuutilization.push_back(s6);
    cpuutilization.push_back(s7);
    cpuutilization.push_back(s8);
    cpuutilization.push_back(s9);
    cpuutilization.push_back(s10);
    return cpuutilization;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    string line;
    string key;
    int value=0;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "processes") {
                    return value;
                }
            }
        }
    }
    return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    string line;
    string key;
    int value=0;
    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "procs_running") {
                    return value;
                }
            }
        }
    }
    return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream stream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
    if (stream.is_open()) {
        std::getline (stream, line);
        return line;
    }
    return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
    string line, key, ram;
    std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream,line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> ram) {
                if (key == "VmSize:") {
                    return ram;
                }
            }
        }
    }
    return string();
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
    string uid;
    string line, key;
    std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
    if(stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> uid) {
                if (key == "Uid:") {
                    return uid;
                }
            }
        }
    }
    return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) {
    string line, username, uid_tofind=std::to_string(uid), donotcare, uid_found;
    std::ifstream stream(kPasswordPath);
    if(stream.is_open()) {
        while(std::getline(stream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> username >> donotcare >> uid_found) {
                if (uid_found == uid_tofind) {
                    return username;
                }
            }
        }
    }
    return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
    int long uptime;
    string s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    string s11, s12, s13, s14, s15, s16, s17, s18, s19, s20;
    string s21, s22;
    string line;
    std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream>>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12>>s13>>s14>>s15>>s16>>s17>>s18>>s19>>s20>>s21>>s22;
            break;
        }
    }
    float hertz = float(sysconf(_SC_CLK_TCK));
    uptime = std::stol(s14) / hertz;
    return uptime;
}