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

#ifndef __wipe_h_
#define __wipe_h_

class Wipe : public Pattern
{
    public:
        
        // constructor
        Wipe (const int32_t width, const int32_t height);

        // constructor
        Wipe 
        (
            const int32_t width, const int32_t height,
			const int32_t direction, const int32_t delay
        );

        // destructor
        ~Wipe (void);

        // reset to first frame in animation
        void init (void);

        // calculate next frame in the animation
        bool next (void);

        // get / set direction of wipe
		// 0 = L to R, 1 = R to L, 2 = T to B, 3 = B to T
        int32_t getDirection (void) {
			return m_direction;
        }
        void setDirection (const int32_t direction) {
            m_direction = direction;
        }

        // get / set delay between steps
        int32_t getDelay (void) {
			return m_delay;
        }
        void setDelay (const int32_t delay) {
            m_delay = delay;
        }

    private:

        int32_t m_direction;
        int32_t m_delay;
		int32_t m_state;
        int32_t m_color;
        int32_t m_timer;
};

#endif
