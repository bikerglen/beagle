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
#include "circle.h"


//---------------------------------------------------------------------------------------------
// constructors
//

Circle::Circle
(
    const int32_t width, const int32_t height
) : 
    Pattern (width, height), 
    m_center_x((width-1.0)/2.0), m_center_y((height-1.0)/2.0),
    m_speed(1.0), m_scale(1.0)
{
    calculateDistanceLut ();
}


Circle::Circle 
(
    const int32_t width, const int32_t height,
    const float center_x, const float center_y,
    const float speed, const float scale
) : 
    Pattern (width, height), 
    m_center_x(center_x), m_center_y(center_y),
    m_speed(speed), m_scale(scale)
{
    calculateDistanceLut ();
}


//---------------------------------------------------------------------------------------------
// destructor
//

Circle::~Circle (void)
{
}


//---------------------------------------------------------------------------------------------
// init -- reset to first frame in animation
//

void Circle::init (void)
{
    m_state = 0;
}


//---------------------------------------------------------------------------------------------
// next -- calculate next frame in animation
//

bool Circle::next (void)
{
    int32_t row, col, distance, hue;

    for (row = 0; row < m_height; row++) {
        for (col = 0; col < m_width; col++) {
            distance = m_scale * 96.0 * m_distance_lut[col][row];
            hue = m_state - distance;
            while (hue < 0) hue += 96;
            while (hue >= 96) hue -= 96;
            gLevels[row][col] = translateHue (hue);
        }
    }

    m_state = m_state + m_speed;
    if (m_state < 0) m_state += 96.0;
    if (m_state >= 96) m_state -= 96.0;

    return (m_state == 0);
}


//---------------------------------------------------------------------------------------------
// calculateDistanceLut
//

void Circle::calculateDistanceLut (void)
{
    // normalize pattern width to a diameter equal to display width
    float tmp_x = (m_width-1.0) / 2.0;
    float tmp_y = (m_width-1.0) / 2.0;
    float norm = sqrt (tmp_x*tmp_x + tmp_y*tmp_y);

    // resize lookup table width if needed
    if (this->m_width != m_distance_lut.size ()) {
      m_distance_lut.resize (this->m_width);
    }

    // iterate over each column
    for (int32_t col = 0; col < this->m_width; col++) {

        // resize lookup table height if needed
        if (this->m_height != m_distance_lut[col].size ()) {
            m_distance_lut[col].resize (this->m_height);
        }

        // iterate over each row
        for (int32_t row = 0; row < this->m_height; row++) {
    
            // find and save normalized distance from each point to center of circle
            float x = col - m_center_x;
            float y = row - m_center_y;
            float distance = sqrt (x*x + y*y) / norm;
            m_distance_lut[col][row] = distance;
        }
    }
}
