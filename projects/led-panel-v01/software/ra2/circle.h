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

#ifndef __circle_h_
#define __circle_h_

class Circle : public Pattern
{
    public:
        
        // constructor
        Circle (const int32_t width, const int32_t height);

        // constructor
        Circle 
        (
            const int32_t width, const int32_t height,
            const float center_x, const float center_y,
            const float speed, const float scale
        );

        // destructor
        ~Circle (void);

        // reset to first frame in animation
        void init (void);

        // calculate next frame in the animation
        bool next (void);

        // get / set center of circle
        void getCenter (float &x, float &y) {
            x = m_center_x; y = m_center_y;
        }
        void setCenter (const float x, const float y) {
            m_center_x = x; m_center_y = y;
            calculateDistanceLut ();
        }

        // get / set scale of the circle
        // 0.5 -> diameter = 2x width of display
        // 1.0 -> diameter = width of panel
        // 2.0 -> diameter = 1/2 width of display
        float getScale (void) {
            return m_scale;
        }
        void setScale (const float scale) {
            m_scale = scale;
        }

        // get set speed
        // this is the increment added/subtracted from the internal state
        // variable after computing each frame of the animation
        float getSpeed (void) {
            return m_speed;
        }
        void setSpeed (const float speed) {
            m_speed = speed;
        }

    private:

        float m_speed;
        float m_scale;
        float m_center_x;
        float m_center_y;
        float m_state;

        void calculateDistanceLut (void);
        vector<vector<float> >  m_distance_lut;

};

#endif
