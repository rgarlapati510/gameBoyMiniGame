#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

typedef struct rabbit {
	int row;
	int col;
} 
Rabbit;

typedef struct carrot {
	int row;
	int col;
}
Carrot;

typedef struct hole {
	int row;
	int col;
}
Hole;

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

#endif
