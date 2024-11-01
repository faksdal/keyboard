// Step 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
// Source: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html


#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>


#define CTRL_KEY(k) ((k) & 0x1f)


struct termios orig_termios;



void die(const char *s)
{
	perror(s);
	exit(1);
}



void disableRawMode(void)
{
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcsetattr");
}



void enableRawMode()
{
	//tcgetattr(STDIN_FILENO, &orig_termios);
	if(tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		die("tcgetattr");

	// diable rawmode upon exit, as a courtesy to the user
	atexit(disableRawMode);

	struct termios raw = orig_termios;

	raw.c_iflag		&= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag		&= ~(OPOST);
	raw.c_cflag		|= (CS8);
	raw.c_lflag		&= ~(ECHO | ICANON | IEXTEN | ISIG);
	//raw.c_cc[VMIN]	= 0;
	//raw.c_cc[VTIME]	= 1;

	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}



int main()
{
	char c;
	


	enableRawMode();

	while (1){
		char c = '\0';
		if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			die("read");

		if(iscntrl(c)) {
			std::cout << (int)c << "\r\n"; //std::endl;
			//printf("%d\r\n", c);
		}
		else{
			std::cout << (int)c << "('" << (char)c << "')\r\n";// << std::endl;
			//printf("%d ('%c')\r\n", c, c);
		}
		if(c == CTRL_KEY('q'))
			break;
	}


	return 0;
}
