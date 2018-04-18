#include <time.h>


clock_t clock_starttime;


void clock_start()
{
	clock_starttime = clock();
}

void clock_reset()
{
	clock_starttime = clock();
}

int clock_get()
{
	return ((clock() - clock_starttime)*1000)/CLOCKS_PER_SEC;
}
