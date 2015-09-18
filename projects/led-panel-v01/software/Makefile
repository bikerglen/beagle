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

CFLAGS:=-fno-omit-frame-pointer -g

all: runcircle runperlin runwash runtwinkle runwipe blank picture blank_n blank_n2

runcircle: runcircle.o pattern.o circle.o globals.o
	g++ $(CFLAGS) -o runcircle $^

runperlin: runperlin.o pattern.o perlin.o globals.o
	g++ $(CFLAGS) -o runperlin $^

runwash: runwash.o pattern.o wash.o globals.o
	g++ $(CFLAGS) -o runwash $^

runtwinkle: runtwinkle.o pattern.o twinkle.o globals.o
	g++ $(CFLAGS) -o runtwinkle $^

runwipe: runwipe.o pattern.o wipe.o globals.o
	g++ $(CFLAGS) -o runwipe $^

globals.o: globals.cpp globals.h
	g++ $(CFLAGS) -c globals.cpp

runcircle.o: runcircle.cpp globals.h pattern.h circle.h
	g++ $(CFLAGS) -c runcircle.cpp

runperlin.o: runperlin.cpp globals.h pattern.h perlin.h
	g++ $(CFLAGS) -c runperlin.cpp

runwash.o: runwash.cpp globals.h pattern.h wash.h
	g++ $(CFLAGS) -c runwash.cpp

runtwinkle.o: runtwinkle.cpp globals.h pattern.h twinkle.h
	g++ $(CFLAGS) -c runtwinkle.cpp

runwipe.o: runwipe.cpp globals.h pattern.h wipe.h
	g++ $(CFLAGS) -c runwipe.cpp

pattern.o: pattern.cpp globals.h gammalut.h pattern.h
	g++ $(CFLAGS) -c pattern.cpp

circle.o: circle.cpp globals.h pattern.h circle.h
	g++ $(CFLAGS) -c circle.cpp

perlin.o: perlin.cpp globals.h pattern.h perlin.h
	g++ $(CFLAGS) -c perlin.cpp

wash.o: wash.cpp globals.h pattern.h wash.h
	g++ $(CFLAGS) -c wash.cpp

twinkle.o: twinkle.cpp globals.h pattern.h twinkle.h
	g++ $(CFLAGS) -c twinkle.cpp

wipe.o: wipe.cpp globals.h pattern.h wipe.h
	g++ $(CFLAGS) -c wipe.cpp

blank: blank.cpp globals.cpp
	g++ $(CFLAGS) -o blank $^

picture: picture.cpp gammalut.h
	g++ $(CFLAGS) -o picture $< globals.cpp

clean:
	rm -f runcircle runperlin runwash runtwinkle runwipe blank picture runcircle.o runperlin.o runwash.o runtwinkle.o pattern.o circle.o perlin.o wash.o twinkle.o wipe.o runwipe.o globals.o
