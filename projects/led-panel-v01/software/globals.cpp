#include "globals.h"

extern uint16_t gLevels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
extern int gFd;
extern int gBuffer;

void WriteLevels (void)
{
    int row, col;

    if (gBuffer == 0) {
	// Buffer 0
    	pwrite (gFd, gLevels, DISPLAY_BUFFER_SIZE, 0);
        gBuffer = 1;
    } else {
	// Buffer 1
    	pwrite (gFd, gLevels, DISPLAY_BUFFER_SIZE, 0x400);
        gBuffer = 0;
    }
}
