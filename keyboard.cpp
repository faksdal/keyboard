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

		/*
		if(!iscntrl(c)){
			printf("Not control key: %d - '%c'\r\n", c, c);
			return c;
		}
		else if(iscntrl(c)){
			char seq[3];

			printf("Control key: %d. Reading sequence...\r\n", c);

			if(read(_fd, &seq[0], 1) == 1){
				printf("seq[0]: %d - '%c'\r\n", seq[0], seq[0]);
			}

			return c;
		}*/
		if(c == 9){
			std::cout << "TAB key pressed\r\n" << std::flush;
			return 9;
		}
		else if(c == 10){
			std::cout << "NUMPAD Enter key pressed\r\n" << std::flush;
			return 10;
		}
		else if(c == 13){
			std::cout << "KEYPAD Enter key pressed\r\n" << std::flush;
			return 13;
		}
		else if(c == 27){
			printf("Control key: %d. Reading sequence...\r\n", c);
			char seq[3];
			if(read(_fd, &seq[0], 1) == 1){
				printf("seq[0]: %d - '%c'\r\n", seq[0], seq[0]);
			}
			if(read(_fd, &seq[1], 1) == 1){
				printf("seq[1]: %d - '%c'\r\n", seq[1], seq[1]);
			}
			if(read(_fd, &seq[2], 1) == 1){
				printf("seq[2]: %d - '%c'\r\n", seq[2], seq[2]);
			}
		}
		else{// if(c != 27){
			printf("Not control key: %d - '%c'\r\n", c, c);
			return c;
		}

	}
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

		key = readKey(fd);
		//printf("Key before switch: %d ('%c')\r\n", key, key);

		if(key != -1){

			switch(key){
				case 9:		std::cout << "TAB pressed\r\n" << std::endl;
							break;
				case 10:	std::cout << "NUMPAD ENTER pressed\r\n" << std::endl;
							break;
				case 13:	std::cout << "KEYBOARD ENTER pressed\r\n" << std::endl;
							break;
				case 'q':	quit = true;
							break;

				default:	printf("Key at switch default: %d ('%c')\r\n", key, key);
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
