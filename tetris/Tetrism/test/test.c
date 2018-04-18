#include <stdio.h>
#include "draw3.h"
#include "clock.h"







int main()
{
	int i, j, time;
	draw_set_coord_size(8, 6);
	draw_init(800, 600);	
	
	clock_start();
	draw_change_color(0.0, 0.0, 1.0);
	
	draw_square(0, 7);
	draw_square(5, 7);
	draw_square(5, 0);
	draw_square(0, 0);

	draw_change_color(0.8, 0.8, 0.8);
	draw_fill_square(0, 7);
	draw_fill_square(5, 7);
	draw_fill_square(5, 0);
	draw_fill_square(0, 0);
	
	draw_swap_buffers();
	time = clock_get();
	printf("Time: %d\n", time);

	while (!draw_should_close()) {draw_poll_events();}

	draw_end();
}
