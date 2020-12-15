CC = g++

CPPFLAGS     = -g -O0 -I../utils -std=gnu++20 -Wall -Werror -Wfatal-errors
CPPFLAGS_OPT =    -O2 -I../utils -std=gnu++20 -Wall -Werror

p1: 
	$(CC) part1.cpp -o part1 $(CPPFLAGS)

p2: 
	$(CC) part2.cpp -o part2 $(CPPFLAGS) 

p1o: 
	$(CC) part1.cpp -o part1 $(CPPFLAGS_OPT)

p2o: 
	$(CC) part2.cpp -o part2 $(CPPFLAGS_OPT) 

all: p1 p2

fast: p1o p2o