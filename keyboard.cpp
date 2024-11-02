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
	int			seqCnt = 0, retkey = -1;
	keyState	state = keyState::NORMAL;
	char		c = '\0';
	char		seq[4];

	if(read(_fd, &c, 1) == 1){
		// If we encounter an escape sequence, we start populate the seq[]
		// and set the appropriate state value
		if(c == 27){
			// If we have indications of an escape sequence, we try another
			// read()
			state = keyState::ESCAPE_SEQ_0;
			if(read(_fd, &seq[seqCnt], 1) > 0){
				seqCnt++;
				state = keyState::ESCAPE_SEQ_1;
				if(read(_fd, &seq[seqCnt], 1) > 0){
					seqCnt++;
					state = keyState::ESCAPE_SEQ_2;
					if(read(_fd, &seq[seqCnt], 1) > 0){
						seqCnt++;
						state = keyState::ESCAPE_SEQ_3;
						if(read(_fd, &seq[seqCnt], 1) > 0){
							state = keyState::ESCAPE_SEQ_4;
						}
					}
				}
			}

		} // if(c = 27)
		switch(state){
			case keyState::NORMAL:			retkey = c;
											break;
			case keyState::ESCAPE_SEQ_0:	retkey = ESC;
											break;
			case keyState::ESCAPE_SEQ_1:	break;
			case keyState::ESCAPE_SEQ_2:	switch(seq[1]){
												case 65:	retkey = UP_ARROW;
															break;
												case 66:	retkey = DOWN_ARROW;
															break;
												case 67:	retkey = RIGHT_ARROW;
															break;
												case 68:	retkey = LEFT_ARROW;
															break;
												case 80:	retkey = F1;
															break;
												case 81:	retkey = F2;
															break;
												case 82:	retkey = F3;
															break;
												case 83:	retkey = F4;
															break;
											}
											break;
			case keyState::ESCAPE_SEQ_3:	switch(seq[1]){
												case 49:	retkey = HOME;
															break;
												case 50:	retkey = INSERT;
															break;
												case 51:	retkey = DELETE;
															break;
												case 52:	retkey = END;
															break;
												case 53:	retkey = PAGE_UP;
															break;
												case 54:	retkey = PAGE_DOWN;
															break;
											}
											break;
			case keyState::ESCAPE_SEQ_4:	std::cout << "keyState::ESCAPE_SEQ_4\r\n" << std::flush;
											break;
			default:						break;
		}

	} // if(read(_fd, &c, 1) == 1)

	return retkey;
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
				case TAB:			std::cout << "TAB pressed\r\n" << std::endl;
									break;
				case NUM_ENTER:		std::cout << "NUMPAD ENTER pressed\r\n" << std::endl;
									break;
				case KB_ENTER:		std::cout << "KEYBOARD ENTER pressed\r\n" << std::endl;
									break;
				case ESC:			std::cout << "ESC pressed - quitting...\r\n" << std::endl;
									quit = true;
									break;
				case UP_ARROW:		std::cout << "UP_ARROW\r\n" << std::flush;
									break;
				case DOWN_ARROW:	std::cout << "DOWN_ARROW\r\n" << std::flush;
									break;
				case RIGHT_ARROW:	std::cout << "RIGHT_ARROW\r\n" << std::flush;
									break;
				case LEFT_ARROW:	std::cout << "LEFT_ARROW\r\n" << std::flush;
									break;
				case F1:			std::cout << "F1\r\n" << std::flush;
									break;
				case F2:			std::cout << "F2\r\n" << std::flush;
									break;
				case F3:			std::cout << "F3\r\n" << std::flush;
									break;
				case F4:			std::cout << "F4\r\n" << std::flush;
									break;
				case HOME:			std::cout << "HOME\r\n" << std::flush;
									break;
				case END:			std::cout << "END\r\n" << std::flush;
									break;
				case INSERT:		std::cout << "INSERT\r\n" << std::flush;
									break;
				case DELETE:		std::cout << "DELETE\r\n" << std::flush;
									break;
				case PAGE_UP:		std::cout << "PAGE_UP\r\n" << std::flush;
									break;
				case PAGE_DOWN:		std::cout << "PAGE_DOWN\r\n" << std::flush;
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
