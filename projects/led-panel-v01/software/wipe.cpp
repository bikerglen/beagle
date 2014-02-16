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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <vector>

using namespace std;

#include "globals.h"
#include "pattern.h"
#include "wipe.h"

static const uint16_t wipeColors[7] = {
    0xf00, 0xff0, 0x0f0, 0x0ff, 0x00f, 0xf0f, 0xccc
};


//---------------------------------------------------------------------------------------------
// constructors
//

Wipe::Wipe
(
    const int32_t width, const int32_t height
) : 
    Pattern (width, height),
	m_direction(0), m_delay(2)
{
}


Wipe::Wipe
(
    const int32_t width, const int32_t height,
	const int32_t direction, const int32_t delay
) : 
    Pattern (width, height),
	m_direction(direction), m_delay(delay)
{
}


//---------------------------------------------------------------------------------------------
// destructor
//

Wipe::~Wipe (void)
{
}


//---------------------------------------------------------------------------------------------
// init -- reset to first frame in animation
//

void Wipe::init (void)
{
	m_state = 0;
	m_color = 0;
	m_timer = 0;
}


//---------------------------------------------------------------------------------------------
// next -- calculate next frame in animation
//

bool Wipe::next (void)
{
	int32_t row, col;

	if (m_timer == 0) {
		for (row = 0; row < m_height; row++) {
			for (col = 0; col < m_width; col++) {

				switch (m_direction) {

					case 0: // left to right 
						if (col == m_state) {
							gLevels[row][col] = wipeColors[m_color];
						}
						break;

					case 1: // right to left 
						if (col == m_state) {
							gLevels[row][m_width - 1 - col] = wipeColors[m_color];
						}
						break;

					case 2: // top to bottom
						if (row == m_state) {
							gLevels[row][col] = wipeColors[m_color];
						}
						break;

					case 3: // bottom to top
						if (row == m_state) {
							gLevels[m_height - 1 - row][col] = wipeColors[m_color];
						}
						break;
				}
			}
		}

		m_state++;
		if (((m_direction <= 1) && (m_state == m_width)) ||
				((m_direction >= 2) && (m_state == m_height))) {
			m_state = 0;
			m_color++;
			if (m_color == 7) {
				m_color = 0;
			}
		}
	}

	m_timer++;
	if (m_timer >= m_delay) {
		m_timer = 0;
	}

	return (m_timer == 0) && (m_color == 0) && (m_state == 0);
}
