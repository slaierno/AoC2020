# CC = g++
CC = /opt/gcc-latest/bin/g++

CPPFLAGS     = -pthread -fconcepts -I../range-v3/include -I../utils -std=gnu++20 -Wall -Werror -ltbb -Wl,-rpath,/opt/gcc-latest/lib64 -Wfatal-errors
CPPFLAGS_OPT = -pthread -fconcepts -I../range-v3/include -I../utils -std=gnu++20 -Wall -Werror -ltbb -Wl,-rpath,/opt/gcc-latest/lib64

p1: 
	$(CC) -g -O0 part1.cpp -o part1 $(CPPFLAGS)

p2: 
	$(CC) -g -O0 part2.cpp -o part2 $(CPPFLAGS) 

p1o: 
	$(CC)    -O3 part1.cpp -o part1 $(CPPFLAGS_OPT)

p2o: 
	$(CC)    -O3 part2.cpp -o part2 $(CPPFLAGS_OPT) 

all: p1 p2

fast: p1o p2o