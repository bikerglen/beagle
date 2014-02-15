#==============================================================================================
# LED Matrix Animated Pattern Generator
# Copyright 2014 by Glen Akins.
# All rights reserved.
# 
# Set editor width to 96 and tab stop to 4.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#==============================================================================================

all: runcircle runperlin runwash runtwinkle blank picture

runcircle: runcircle.o pattern.o circle.o 
	g++ -o runcircle runcircle.o pattern.o circle.o 

runperlin: runperlin.o pattern.o perlin.o 
	g++ -o runperlin runperlin.o pattern.o perlin.o 

runwash: runwash.o pattern.o wash.o 
	g++ -o runwash runwash.o pattern.o wash.o 

runtwinkle: runtwinkle.o pattern.o twinkle.o 
	g++ -o runtwinkle runtwinkle.o pattern.o twinkle.o 

runcircle.o: runcircle.cpp globals.h pattern.h circle.h
	g++ -c runcircle.cpp

runperlin.o: runperlin.cpp globals.h pattern.h perlin.h
	g++ -c runperlin.cpp

runwash.o: runwash.cpp globals.h pattern.h wash.h
	g++ -c runwash.cpp

runtwinkle.o: runtwinkle.cpp globals.h pattern.h twinkle.h
	g++ -c runtwinkle.cpp

pattern.o: pattern.cpp globals.h gammalut.h pattern.h
	g++ -c pattern.cpp

circle.o: circle.cpp globals.h pattern.h circle.h
	g++ -c circle.cpp

perlin.o: perlin.cpp globals.h pattern.h perlin.h
	g++ -c perlin.cpp

wash.o: wash.cpp globals.h pattern.h wash.h
	g++ -c wash.cpp

twinkle.o: twinkle.cpp globals.h pattern.h twinkle.h
	g++ -c twinkle.cpp

blank: blank.cpp
	g++ -o blank blank.cpp

picture: picture.cpp gammalut.h
	g++ -o picture picture.cpp

clean:
	rm -f runcircle runperlin runwash runtwinkle blank picture runcircle.o runperlin.o runwash.o runtwinkle.o pattern.o circle.o perlin.o wash.o twinkle.o
