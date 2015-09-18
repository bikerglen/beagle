#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <memory.h>

#include "globals.h"

uint16_t gLevels[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int gFd = 0;
int gBuffer = 0;

int main (int argc, char *argv[])
{
    // open fpga memory device
    gFd = open ("/dev/logibone_mem", O_RDWR | O_SYNC);

    // fill buffer 0 with black
    for (int row = 0; row < 32; row++) {
        for (int col = 0; col < 32; col++) {
            gLevels[row][col] = 0;
        }
    }
    
    WriteLevels();

    // close fpga device
    close (gFd);

    return 0;
}

