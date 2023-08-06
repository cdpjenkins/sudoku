PREFIX=~/opt/cross-mint-12.2.0-thorsten-20230112/bin/m68k-atari-mint-

CXXFLAGS=-O3 -m68000
CC=$(PREFIX)gcc
CXX=$(PREFIX)g++
AS=$(PREFIX)as

all: cpp-sudoku

cpp-sudoku: main.o Sudoku.o
	${CXX} ${CXXFLAGS} main.o Sudoku.o -o cpp-sudoku -lgcc

%.o : ../src/%.cpp ../src/*.hpp
	${CXX} -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o cpp-sudoku