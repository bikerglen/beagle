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
#include "twinkle.h"


//---------------------------------------------------------------------------------------------
// constructors
//

Twinkle::Twinkle
(
    const int32_t width, const int32_t height
) : 
    Pattern (width, height)
{
	this->resize ();
}


//---------------------------------------------------------------------------------------------
// destructor
//

Twinkle::~Twinkle (void)
{
}


//---------------------------------------------------------------------------------------------
// resize state, hue, value arrays
//

void Twinkle::resize (void)
{
	m_twinklers.resize (m_height);
	for (int32_t row = 0; row < m_height; row++) {
		m_twinklers[row].resize (m_width);
	}
}


//---------------------------------------------------------------------------------------------
// init -- reset to first frame in animation
//

void Twinkle::init (void)
{
	for (int32_t row = 0; row < m_height; row++) {
		for (int32_t col = 0; col < m_width; col++) {
			m_twinklers[row][col].state = 0;
			m_twinklers[row][col].hue = 0;
			m_twinklers[row][col].percent = 0;
		}
	}
}


//---------------------------------------------------------------------------------------------
// next -- calculate next frame in animation
//

bool Twinkle::next (void)
{
	for (int32_t row = 0; row < m_height; row++) {
		for (int32_t col = 0; col < m_width; col++) {
			int32_t r = rand();
			switch (m_twinklers[row][col].state) {

				case 0: // off
					if (r < (0.025*RAND_MAX)) {
						m_twinklers[row][col].state = 1;
						m_twinklers[row][col].hue = r % 96;
						m_twinklers[row][col].percent = 10;
						gLevels[row][col] = translateHueValue (m_twinklers[row][col].hue, 
							(float)m_twinklers[row][col].percent/100.0);
					}
					break;

				case 1: // ramp up
						m_twinklers[row][col].percent += 10;
						gLevels[row][col] = translateHueValue (m_twinklers[row][col].hue, 
							(float)m_twinklers[row][col].percent/100.0);
						if (m_twinklers[row][col].percent == 100) {
							m_twinklers[row][col].state = 2;
						}
					break;
				case 2: // on
					if (r < (0.20*RAND_MAX)) {
						m_twinklers[row][col].state = 3;
					}
					break;
				case 3: // ramp down
						m_twinklers[row][col].percent -= 10;
						gLevels[row][col] = translateHueValue (m_twinklers[row][col].hue, 
							(float)m_twinklers[row][col].percent/100.0);
						if (m_twinklers[row][col].percent == 0) {
							m_twinklers[row][col].state = 0;
						}
					break;

			}
		}
	}

    return true;
}
