
#include "scheduler.h"

Scheduler scheduler;

//----------------------------------

bool Scheduler::every(

unsigned long interval,

unsigned long &timer

)

{

    if(

    millis()-timer>=interval

    )

    {

        timer=millis();

        return true;

    }

    return false;

}
