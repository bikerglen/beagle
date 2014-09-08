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

#ifndef __twinkle_h_
#define __twinkle_h_

typedef struct {
	uint8_t state;
	uint8_t hue;
	uint8_t percent;
} Twinkler;

class Twinkle : public Pattern
{
    public:
        
        // constructor
        Twinkle (const int32_t width, const int32_t height);

        // destructor
        ~Twinkle (void);

        // reset to first frame in animation
        void init (void);

        // calculate next frame in the animation
        bool next (void);

    private:

		void resize (void);
        vector<vector<Twinkler> > m_twinklers;
};

#endif
