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
//
// Major inspiration for the use of Perlin noise to generate pseudorandom RGB patterns comes
// from the TI RGB LED coffee table project and the following resources:
//
// TI RGB LED Coffee Table:
//
//  http://e2e.ti.com/group/microcontrollerprojects/m/msp430microcontrollerprojects/447779.aspx
//  https://github.com/bear24rw/rgb_table/tree/master/code/table_drivers/pytable
//
// Casey Duncan's Python C Noise Library:
//
//  https://github.com/caseman/noise
//
// Ken Perlin's Original Source Code:
//
//  http://www.mrl.nyu.edu/~perlin/doc/oscar.html
//
// Excellent explanation of Perlin noise here:
// 
//  http://webstaff.itn.liu.se/~stegu/TNM022-2005/perlinnoiselinks/perlin-noise-math-faq.html
//=============================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

#include "globals.h"
#include "pattern.h"
#include "perlin.h"


//---------------------------------------------------------------------------------------------
// constructors
//

Perlin::Perlin 
(
    const int32_t width, const int32_t height, const int32_t mode
) : 
    Pattern (width, height), 
    m_mode (mode), m_xy_scale(8.0/64.0), 
    m_z_step(0.0125), m_z_depth(512.0), 
    m_hue_options(0.005)
{
}


Perlin::Perlin (
    const int32_t width, const int32_t height,
    const int32_t mode, const float xy_scale, 
    const float z_step, const float z_depth, 
    const float hue_options
) : 
    Pattern (width, height), 
    m_mode (mode), m_xy_scale(xy_scale), 
    m_z_step(z_step), m_z_depth(z_depth), 
    m_hue_options(hue_options)
{
}


//---------------------------------------------------------------------------------------------
// destructor
//

Perlin::~Perlin (void)
{
}


//---------------------------------------------------------------------------------------------
// init -- reset to first frame in animation
//

void Perlin::init (void)
{
    // reset to z=0 plane
    m_z_state = 0.0;

    // reset to red, only used for modes two and three
    m_hue_state = 0.0;

    // reset normalization min and max 
    m_min = 0.0001;
    m_max = 0.0001;
}


//---------------------------------------------------------------------------------------------
// next -- calculate next frame in animation
//

bool Perlin::next (void)
{
    int32_t x, y;
    float sx, sy, n1, n2, n;
    int32_t hue;

    // row
    for (y = 0; y < m_height; y++) {

        // scale y
        sy = (float)y * m_xy_scale;

        // column
        for (x =0; x < m_width; x++) {

            // scale x
            sx = (float)x * m_xy_scale;

            // generate noise at plane z_state
            n1 = this->noise (sx, sy, m_z_state);

            // generate noise at plane z_depth - z_state 
            n2 = this->noise (sx, sy, m_z_state - m_z_depth);

            // combine noises
            n = ((m_z_depth - m_z_state) * n1 + (m_z_state) * n2) / m_z_depth;

            // normalize combined noises to a number between 0 and 1
            if (n > m_max) m_max = n;
            if (n < m_min) m_min = n;
            n = n + fabs (m_min);               // make noise a positive value
            n = n / (m_max + fabs (m_min));     // scale noise to between 0 and 1

            // set hue and/or brightness based on mode
            switch (m_mode) {
        
                // base hue fixed, varies based on noise
                case 1:
                    hue = (m_hue_options + n)*96.0 + 0.5;
                    hue = hue % 96;
                    gLevels[y][x] = this->translateHue (hue);
                    break;

                // hue rotates at constant velocity, varies based on noise
                case 2:
                    hue = (m_hue_state + n)*96.0 + 0.5;
                    hue = hue % 96;
                    gLevels[y][x] = this->translateHue (hue);
                    break;

                // hue rotates at constant velocity, brightness varies based on noise
                case 3: 
                    hue = (m_hue_state)*96.0 + 0.5;
                    hue = hue % 96;
                    gLevels[y][x] = this->translateHueValue (hue, n);
                    break;

                // undefined mode, blank display
                default:
                    gLevels[x][y] = 0;
                    break;

            }
        }
    }

    // update state variables
    m_z_state = fmod (m_z_state + m_z_step, m_z_depth);
    m_hue_state = fmod (m_hue_state + m_hue_options, 1.0);

    return true;
}


//---------------------------------------------------------------------------------------------
// noise
//

#define lerp(t, a, b) ((a) + (t) * ((b) - (a)))

static const float GRAD3[][3] = {
    {1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0}, 
    {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1}, 
    {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1},
    {1,0,-1},{-1,0,-1},{0,-1,1},{0,1,1}};

static const unsigned char PERM[] = {
  151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
  36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
  234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
  88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
  134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
  230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
  1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
  116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
  124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
  47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
  154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
  108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
  242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
  239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
  50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
  141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131,
  13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
  240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
  219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125,
  136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158,
  231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245,
  40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187,
  208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198,
  173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
  255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223,
  183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167,
  43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185,
  112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179,
  162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199,
  106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236,
  205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156,
  180};

float inline grad3(const int hash, const float x, const float y, const float z)
{
    const int h = hash & 15;
    return x * GRAD3[h][0] + y * GRAD3[h][1] + z * GRAD3[h][2];
}

float Perlin::noise (float x, float y, float z)
{
    float fx, fy, fz;
    int A, AA, AB, B, BA, BB;

	// find nearest whole number to each input coordinate
    int i = (int)floorf(x);
    int j = (int)floorf(y);
    int k = (int)floorf(z);
    int ii = i + 1;
    int jj = j + 1;
    int kk = k + 1;

	// ensure all inputs to permutation functions are between 0 and 255
	i &= 0xff;
	ii &= 0xff;
	j &= 0xff;
	jj &= 0xff;
	k &= 0xff;
	kk &= 0xff;

	// convert each input to a number between 0 and 1
    x -= floorf(x); y -= floorf(y); z -= floorf(z);

	// apply easing function
    fx = x*x*x * (x * (x * 6 - 15) + 10);
    fy = y*y*y * (y * (y * 6 - 15) + 10);
    fz = z*z*z * (z * (z * 6 - 15) + 10);

	// apply permutation function
    A = PERM[i];
    AA = PERM[A + j];
    AB = PERM[A + jj];
    B = PERM[ii];
    BA = PERM[B + j];
    BB = PERM[B + jj];

	// six linear interpolations
    return lerp(fz, lerp(fy, lerp(fx, grad3(PERM[AA + k], x, y, z),
                                      grad3(PERM[BA + k], x - 1, y, z)),
                             lerp(fx, grad3(PERM[AB + k], x, y - 1, z),
                                      grad3(PERM[BB + k], x - 1, y - 1, z))),
                    lerp(fy, lerp(fx, grad3(PERM[AA + kk], x, y, z - 1),
                                      grad3(PERM[BA + kk], x - 1, y, z - 1)),
                             lerp(fx, grad3(PERM[AB + kk], x, y - 1, z - 1),
                                      grad3(PERM[BB + kk], x - 1, y - 1, z - 1))));
}
