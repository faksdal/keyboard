/*
 * enableRawMode.cpp
 *
 *  Created on: 2 Nov 2024
 *      Author: jole
 */

#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>

#include "keyboard.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void keyboard::enableRawMode(void)
{
	struct termios raw = originalTermios;


	tcgetattr(fd, &originalTermios);

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	//raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // I want ISIG on
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(fd, TCSAFLUSH, &raw);
}


