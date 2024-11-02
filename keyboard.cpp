// Step 8 - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
// ASCII-table https://www.asciitable.com/

#include <iostream>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "keymapping.h"

int readKey(int _fd);
void processKey(int _fd);

struct termios orig_termios;



void disableRawMode()
{
	std::cout << "disableRawMode\r\n";

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}



void enableRawMode(void)
{
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  //raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



void processKey(int _fd)
{
}



int readKey(int _fd)
{
	char c = '\0';

	if(read(_fd, &c, 1) == 1){
		switch(c){
			case TAB:		return TAB;
							//break;
			case NUM_ENTER:	return NUM_ENTER;
							//break;
			case KB_ENTER:	return KB_ENTER;
							//break;
			case ESC:		// Might be an escape sequence, or just the ESC key,
							// we have to check...
							printf("Control key: %d. Reading sequence...\r\n", c);

							// Next read()'s go into this
							char seq[3];

							// Try to read the first byte into seq[0]
							// If read() returns 0, it means there are no more
							// characters in the buffer, indicating the user
							// pressed ESC.
							if(read(_fd, &seq[0], 1) == 0){
								std::cout << "ESC key pressed\r\n" << std::flush;

								return ESC;
							}
							// Otherwise, if read() returns a non-zero value,
							// we check to figure out what key the user hit.
							else{
								std::cout << "We have an escape sequence...\r\n";
								printf("seq[0] %d - '%c'\r\n", seq[0], seq[0]);
								return -1;
							}
							//break;
			default:		printf("Regular key: %d - '%c' pressed\r\n", c, c);
							return c;
							//break;
		}

	} // if(read(_fd, &c, 1) == 1)
	return -1;
}



int main()
{
	int fd		= STDIN_FILENO;
	int key;
	bool	quit = false;




	enableRawMode();

	while(!quit){
		//char c = '\0';
		//char c = 'a';
		//read(STDIN_FILENO, &c, 1);

		//key = readKey(fd);
		//printf("Key before switch: %d ('%c')\r\n", key, key);

		//if(key != -1){
		if((key = readKey(fd)) != -1){
			switch(key){
				case TAB:		std::cout << "TAB pressed\r\n" << std::endl;
								break;
				case NUM_ENTER:	std::cout << "NUMPAD ENTER pressed\r\n" << std::endl;
								break;
				case KB_ENTER:	std::cout << "KEYBOARD ENTER pressed\r\n" << std::endl;
								break;
				case ESC:		std::cout << "ESC pressed\r\n" << std::endl;
								break;
				case 'q':		quit = true;
								break;

				default:		printf("Key at switch default: %d ('%c')\r\n", key, key);
								break;
			} // switch(key)
		} // if(key != -1)

		/*
		if (iscntrl(c)){
			printf("ESC-Sequence: %d\r\n", c);
		}
		else{
			printf("Regular: %d ('%c')\r\n", c, c);
		}
		*/

		//if (c == 'q') break;
	}

	/*
	while(!quit){
		//while(int nread = read(fd, &c, 1) == 1 && c != 'q'){
		int nread = read(fd, &c, 1);

		printf("Counter: %d\r\n", ++counter);
		printf("read() return value: %d\r\n", nread);

		if(iscntrl(c)){
			read(fd, &c, 1);
			printf("ESC-sequence: %d\n", c);
			read(fd, &c, 1);
			printf("ESC-sequence: %d\n", c);

		}

		else{
			printf("Regular char: %d ('%c')\n", c, c);
		}

		if(c == 'q')
			quit = true;

	} // while(!quit)
	*/

	//disableRawMode();
	return 0;
}
