#include <ncurses.h>

int main(void)
{
	initscr();
	printw("Hello Jon");
	refresh();
	getch();
	endwin();
	return 0;
}
