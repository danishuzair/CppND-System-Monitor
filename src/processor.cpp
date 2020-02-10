#include "processor.h"

// TODO: Return the aggregate CPU utilization

void Processor::CalculateUtilization() {
    std::vector<std::string> processorutilization_s = LinuxParser::CpuUtilization();
    long user = std::stol(processorutilization_s[0]);
    long nice = std::stol(processorutilization_s[1]);
    long system = std::stol(processorutilization_s[2]);
    long idle = std::stol(processorutilization_s[3]);
    long iowait = std::stol(processorutilization_s[4]);
    long irq = std::stol(processorutilization_s[5]);
    long softirq = std::stol(processorutilization_s[6]);
    long steal = std::stol(processorutilization_s[7]);

    long previous_idle_full = previous_idle + previous_iowait;
    long idle_full = idle + iowait;
    long previous_nonidle = previous_user + previous_nice + previous_system + previous_irq + previous_softirq + previous_steal;
    long nonidle = user + nice + system + irq + softirq + steal;
    long previous_total = previous_idle_full + previous_nonidle;
    long total = idle_full + nonidle;

    long total_difference = total - previous_total;
    long idle_difference = idle_full - previous_idle_full;
    processorutilization = (float(total_difference) - float(idle_difference)) / float(total_difference);

    previous_user=user;
    previous_nice=nice;
    previous_system=system;
    previous_idle=idle;
    previous_iowait=iowait;
    previous_irq=irq;
    previous_softirq=softirq;
    previous_steal=steal;
}

float Processor::Utilization() {
    CalculateUtilization();
    return processorutilization;
}