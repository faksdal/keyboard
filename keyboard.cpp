/*
 * keyboard.cpp
 *
 *  Created on: 2 Nov 2024
 *      Author: jole
 */

// Resources:
//		- Step 8 - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
//		- ASCII-table https://www.asciitable.com/
//		- https://www.man7.org/linux/man-pages/man2/read.2.html

//#include <iostream>

//#include <unistd.h>
//#include <termios.h>

#include "keyboard.h"



keyboard::keyboard(int _fd)
{
	fd = _fd;
	//fd = STDIN_FILENO;
	enableRawMode();
}



keyboard::~keyboard()
{
	disableRawMode();
}
