#pragma once

typedef struct time {
	int hour, min;
} Time;

int timeDiff(Time time1,Time time2);
int timeDiffSpecial(Time time1,Time time2);

