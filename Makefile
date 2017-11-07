CC = g++
	# compiler flags:
  	#  -g    adds debugging information to the executable file
  	#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: sample.cpp
	g++ -g -Wall -std=c99 -o Zcash ZcashParser.cpp

clean: 
	$(RM) Zcash
