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

all: runpf2

runpf2: runpf2.o pattern.o pf2.o 
	g++ -o runpf2 runpf2.o pattern.o pf2.o 

runpf2.o: runpf2.cpp globals.h pattern.h pf2.h
	g++ -c -O3 runpf2.cpp

pattern.o: pattern.cpp globals.h gammalut.h pattern.h
	g++ -c pattern.cpp

pf2.o: pf2.cpp globals.h pattern.h pf2.h
	g++ -c -O3 pf2.cpp

clean:
	rm -f pattern.o pf2.o runpf2.o runpf2
