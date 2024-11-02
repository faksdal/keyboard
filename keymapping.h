/*
 * keymapping.h
 *
 *  Created on: 2 Nov 2024
 *      Author: jole
 */
#pragma once

enum KEYMAP{
	TAB			= 9,
	NUM_ENTER	= 10,
	KB_ENTER	= 13,
	ESC			= 27,
	BK_SP		= 127,

	// These needs to be user defined, since they return regular characters
	UP_ARROW	= 1000,
	DOWN_ARROW,
	RIGHT_ARROW,
	LEFT_ARROW
};

/*
----------------------------------------------------------------------
|key			|escape|  seq[0]  |  seq[1]  |   seq2]   |  seq[3]   |
----------------------------------------------------------------------
|ESC			|  27  |          |          |           |           |
|TAB			|   9  |          |          |           |           |
|BK_SP  		| 127  |          |          |           |           |
|KB_ENTER		|  13  |          |          |           |           |
|NUM_ENTER		|  10  |          |          |           |           |
----------------------------------------------------------------------
|UP_ARROW		|  27  | 91 - '[' | 65 - 'A' |           |           |
|DOWN_ARROW		|  27  | 91 - '[' | 66 - 'B' |           |           |
|RIGHT_ARROW	|  27  | 91 - '[' | 67 - 'C' |           |           |
|LEFT_ARROW		|  27  | 91 - '[' | 68 - 'D' |           |           |
----------------------------------------------------------------------
|INSERT			|  27  | 91 - '[' | 50 - '2' | 126 - '~' |           |
|DELETE			|  27  | 91 - '[' | 51 - '3' | 126 - '~' |           |
|HOME			|  27  | 91 - '[' | 49 - '1' | 126 - '~' |           |
|END			|  27  | 91 - '[' | 54 - '4' | 126 - '~' |           |
|PAGE_UP		|  27  | 91 - '[' | 53 - '5' | 126 - '~' |           |
|PAGE_DOWN		|  27  | 91 - '[' | 54 - '6' | 126 - '~' |           |
----------------------------------------------------------------------
|F1				|  27  | 79 - 'O' | 80 - 'P' |           |           |
|F2				|  27  | 79 - 'O' | 81 - 'Q' |           |           |
|F3				|  27  | 79 - 'O' | 82 - 'R' |           |           |
|F4				|  27  | 79 - 'O' | 83 - 'S' |           |           |
|F5				|  27  | 91 - '[' | 49 - '1' | 53 - '5'  | 126 - '~' |
|F6				|  27  | 91 - '[' | 49 - '1' | 55 - '7'  | 126 - '~' |
|F7				|  27  | 91 - '[' | 49 - '1' | 56 - '8'  | 126 - '~' |
|F8				|  27  | 91 - '[' | 49 - '1' | 57 - '9'  | 126 - '~' |
|F9				|  27  | 91 - '[' | 50 - '2' | 48 - '0'  | 126 - '~' |
|F10			|  27  | 91 - '[' | 50 - '2' | 49 - '1'  | 126 - '~' |
|F11			|  27  | 91 - '[' | 50 - '2' | 51 - '3'  | 126 - '~' |
|F12			|  27  | 91 - '[' | 50 - '2' | 52 - '4'  | 126 - '~' |
----------------------------------------------------------------------

*/
