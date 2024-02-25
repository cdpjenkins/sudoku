# Build for Atari ST/TT/TOS machine

What's that, you want to solve a Sudoku on an old 16/32 bit Atari machine? The Makefile in this directory will build
the C++ Sudoku solver for such a machine. I build using a cross-mint toolchain on Mac/Linux; I'm not sure if this
code will compile using GCC 4.6.4 (which is the latest version of GCC that I have running on FreeMiNT on an emulated
Atari machine) but cross-mint GCC 13 on my Mac copes with it fine.

It runs pretty quickly on Aranym and even runs acceptably quickly on an (emulated) ST, which is nice.
