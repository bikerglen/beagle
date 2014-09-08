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
#include "wash.h"


//---------------------------------------------------------------------------------------------
// constructors
//

Wash::Wash
(
    const int32_t width, const int32_t height
) : 
    Pattern (width, height),
	m_step(1.0), m_scale(1.0)
{
}


Wash::Wash
(
    const int32_t width, const int32_t height,
	const float step, const float scale, const float angle
) : 
    Pattern (width, height),
	m_step(step), m_scale(scale), m_angle(angle)
{
}


//---------------------------------------------------------------------------------------------
// destructor
//

Wash::~Wash (void)
{
}


//---------------------------------------------------------------------------------------------
// init -- reset to first frame in animation
//

void Wash::init (void)
{
	m_state = 0;
}


//---------------------------------------------------------------------------------------------
// next -- calculate next frame in animation
//

bool Wash::next (void)
{
	int32_t row, col, hue;

	float rads = m_angle*M_PI/180.0;
	for (row = 0; row < m_height; row++) {
		float x = row - ((m_width-1.0)/2.0);
		for (col = 0; col < m_width; col++) {
			float y = ((m_height-1.0)/2.0) - col;
			float xp = x * cos (rads) - y * sin (rads);
			// float yp = x * sin (rads) + y * cos (rads);
			hue = m_state + m_scale * xp + 0.5;
			while (hue < 0) hue += 96;
			while (hue >= 96) hue -= 96;
			gLevels[row][col] = translateHue (hue);
		}
	}

	m_state = fmod ((m_state + m_step), 96.0);

    return (m_state == 0);
}
