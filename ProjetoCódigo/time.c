#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "time.h"
#include "input.h"

Time createTime(int hour, int min){
    Time t;
    t.hour=hour;
    t.min=min;
    return t;
}

int timeDiff(Time time1,Time time2) {
    // if time2 goes after midnight and time is before midnight
    if (time2.hour < time1.hour)
        //time2.hour = 24-time2.hour;
        time2.hour = 24+time2.hour;
    return (time2.hour - time1.hour) * 60 + (time2.min - time1.min);
}


// Calculate the time difference between time1 and time2, in minutes
// timeDiffSpecial = time2-time1
int timeDiffSpecial(Time time1,Time time2) {
    int aux = (time2.hour - time1.hour) * 60 + (time2.min - time1.min);
    if (aux < -70) 
        aux = ( (time2.hour+24) - time1.hour) * 60 + (time2.min - time1.min);
    else if (aux > 1100) 
        aux = ( time2.hour - (time1.hour+24)) * 60 + (time2.min - time1.min);
    return aux;
}
