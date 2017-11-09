CC = g++
	# compiler flags:
  	#  -g    adds debugging information to the executable file
  	#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

all: sample.cpp
	g++ -g -Wall -o Zcash test_parser_ZECv2/src/ZcashParser.cpp

clean: 
	$(RM) Zcash
