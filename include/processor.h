#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    void CalculateUtilization();
    float processorutilization;
//    long user, nice, system, idle, iowait, irq, softirq, steal;
    long previous_user=0, previous_nice=0, previous_system=0, previous_idle=0;
    long previous_iowait=0, previous_irq=0, previous_softirq=0, previous_steal=0;

};

#endif