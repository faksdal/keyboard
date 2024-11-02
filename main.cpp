/*
 * main.cpp
 *
 *  Created on: 2 Nov 2024
 *      Author: jole
 */

#include <iostream>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "keyboard.h"



// Driver code
int main(void)
{
	int			key;
	int			fd		= STDIN_FILENO;
	bool		quit	= false;
	keyboard	kb(fd);

	while(!quit){
		if((key = kb.readkey()) != -1){
			switch(key){
				case TAB:			std::cout << "TAB pressed\r\n" << std::flush;
									break;
				case NUM_ENTER:		std::cout << "NUMPAD ENTER pressed\r\n" << std::flush;
									break;
				case KB_ENTER:		std::cout << "KEYBOARD ENTER pressed\r\n" << std::flush;
									break;
				case ESC:			std::cout << "ESC pressed - quitting...\r\n" << std::flush;
									quit = true;
									break;
				case BK_SP:			std::cout << "BK_SP pressed\r\n" << std::flush;
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
				case F5:			std::cout << "F5\r\n" << std::flush;
									break;
				case F6:			std::cout << "F6\r\n" << std::flush;
									break;
				case F7:			std::cout << "F7\r\n" << std::flush;
									break;
				case F8:			std::cout << "F8\r\n" << std::flush;
									break;
				case F9:			std::cout << "F9\r\n" << std::flush;
									break;
				case F10:			std::cout << "F10\r\n" << std::flush;
									break;
				case F11:			std::cout << "F11\r\n" << std::flush;
									break;
				case F12:			std::cout << "F12\r\n" << std::flush;
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
				default:			std::cout << (char)key << std::flush;
									break;
			} // switch(key)
		} // if(key != -1)
		//std::cout << "Waiting...\r\n";
	} // while(!quit)

	return 0;
}
