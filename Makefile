CC=g++
CFLAGS= -Wall -g

puzzle: main.cpp
	$(CC) -o puzzle.exe main.cpp problem.cpp puzzlemake.cpp
