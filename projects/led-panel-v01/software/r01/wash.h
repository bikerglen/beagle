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

#ifndef __wash_h_
#define __wash_h_

class Wash : public Pattern
{
    public:
        
        // constructor
        Wash (const int32_t width, const int32_t height);

        // constructor
        Wash 
        (
            const int32_t width, const int32_t height,
            const float step, const float scale, const float angle
        );

        // destructor
        ~Wash (void);

        // reset to first frame in animation
        void init (void);

        // calculate next frame in the animation
        bool next (void);

        // get / set step, controls speed of wash
        float getStep (void) {
			return m_step;
        }
        void setStep (const float step) {
            m_step = step;
        }

        // get / set scale, controls width of wash
        float getScale (void) {
			return m_scale;
        }
        void setScale (const float scale) {
            m_scale = scale;
        }

		// get / set angle
        float getAngle (void) {
			return m_angle;
        }
        void setAngle (const float angle) {
            m_angle = angle;
        }

    private:

        float m_step;
        float m_scale;
		float m_angle;
        float m_state;
};

#endif
