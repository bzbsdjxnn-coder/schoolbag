
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

class Scheduler {
public:

  bool every(
    unsigned long interval,
    unsigned long &timer);
};

extern Scheduler scheduler;

#endif
