//=============================================================================================
// LED Matrix Animated Pattern Generator
// Copyright 2014 by Glen Akins.
// All rights reserved.
// 
// Set editor width to 96 and tab stop to 4.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//=============================================================================================

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
#include <vector>

using namespace std;

#include "globals.h"
#include "pattern.h"
#include "pf2.h"

// address register
#define FPGA_PANEL_ADDR_REG 0x0010

// data register
#define FPGA_PANEL_DATA_REG 0x0012

// buffer select register
#define FPGA_PANEL_BUFFER_REG 0x0014

// global dimming 0 to 0x100
#define FPGA_PANEL_DIMMING_REG 0x0016

// test pin
#define FPGA_TEST_PIN_REG 0x0018

// file descriptor for FPGA memory device
int gFd = 0;

// FPGA frame buffer select
int32_t gBuffer = 0;

// global levels to write to FPGA
uint16_t gLevels[DISPLAY_HEIGHT][DISPLAY_WIDTH];

// global object to create animated pattern
Perlin *gPattern = NULL;

// prototypes
void Quit (int sig);
void BlankDisplay (void);
void Write16 (uint16_t address, uint16_t data);
void WriteLevels (void);
void timer_handler (int signum);

int main (int argc, char *argv[])
{
    struct sigaction sa;
    struct itimerval timer;

    // trap ctrl-c to call quit function 
    signal (SIGINT, Quit);

    // open fpga memory device
    gFd = open ("/dev/logibone_mem", O_RDWR | O_SYNC);

    // initialize levels to all off
    BlankDisplay ();

    // create a new pattern object -- perlin noise, mode 2 long repeating
    gPattern = new Perlin (DISPLAY_WIDTH, DISPLAY_HEIGHT, 2, 4.0/64.0, 1.0/64.0, 256.0, 0.005);

    // create a new pattern object -- perlin noise, mode 1 short repeat
    // gPattern = new Perlin (DISPLAY_WIDTH, DISPLAY_HEIGHT, 1, 8.0/64.0, 0.0125, 1.0, 0.2);

    // reset to first frame
    gPattern->init ();

    // install timer handler
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &timer_handler;
    sigaction (SIGALRM, &sa, NULL);

    // configure the timer to expire after 20 msec
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 20000;

    // and every 20 msec after that.
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 20000;

    // start the timer
    setitimer (ITIMER_REAL, &timer, NULL);

    // wait forever
    while (1) {
        sleep (1);
    }

    // delete pattern object
    delete gPattern;

    // close fpga device
    close (gFd);

    return 0;
}


void Quit (int sig)
{
    if (gFd != 0) {
        close (gFd);
        gFd = 0;
    }
    exit (-1);
}


void BlankDisplay (void)
{
    // initialize levels to all off
    for (int32_t row = 0; row < DISPLAY_HEIGHT; row++) {
        for (int32_t col = 0; col < DISPLAY_WIDTH; col++) {
            gLevels[row][col] = 0x0000;
        }
    }

    // send levels to board
    WriteLevels ();
}


void Write16 (uint16_t address, uint16_t data)
{
    pwrite (gFd, &data, 2, address);
}


void WriteLevels (void)
{
    int base, row, col;

	// ping pong between buffers
	if (gBuffer == 0) {
		base = 0x0000;
	} else {
		base = 0x2000;
	}

    // write data to selected buffer
    for (row = 0; row < DISPLAY_HEIGHT; row++) {
		Write16 (FPGA_PANEL_ADDR_REG, base + 0x80 * row);
        for (col = 0; col < DISPLAY_WIDTH; col++) {
            Write16 (FPGA_PANEL_DATA_REG, gLevels[row][col]);
        }
    }

    // make that buffer active
    if (gBuffer == 0) {
        Write16 (FPGA_PANEL_BUFFER_REG, 0x0000);
        gBuffer = 1;
    } else {
        Write16 (FPGA_PANEL_BUFFER_REG, 0x0001);
        gBuffer = 0;
    }
}


void timer_handler (int signum)
{
    // write levels to display
    WriteLevels ();

    // calculate next frame in animation
    if (gPattern != NULL) {
		Write16 (0x0018, 0x0001);
        bool patternComplete = gPattern->next ();
		Write16 (0x0018, 0x0000);
    }
}
