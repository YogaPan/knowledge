#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(void)
{
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int direction;

	x = 0;
	y = 0;
	direction = 1;

	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, max_y, max_x);

	while (1) {
		clear();
		mvprintw(y, x, "o");
		refresh();
		usleep(DELAY);

		next_x = x + direction;
		if (next_x >= max_x || next_x < 0)
			direction *= -1;
		else
			x += direction;
	}

	endwin();
	return 0;
}
