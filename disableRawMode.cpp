/*
 * disableRawMode.cpp
 *
 *  Created on: 2 Nov 2024
 *      Author: jole
 */
//#include <iostream>

//#include <unistd.h>
//#include <termios.h>

#include "keyboard.h"



void keyboard::disableRawMode(void)
{
	tcsetattr(fd, TCSAFLUSH, &originalTermios);
}
