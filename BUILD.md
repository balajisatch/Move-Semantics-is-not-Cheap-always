# How to build

## In a linux like system

### PRE-REQUISITES

  - GCC with >C++11 support.
  - Google benchmark - https://github.com/google/benchmark.

### Normal compilation

There is a simple makefile defined. Just execute the following command,

>make vect

An executable named vectorCopyMove will be created. Just execute the executable in your terminal.

## Working with kcachegrind

### Prerequisites

   - Valgrind, kcachegrind - http://kcachegrind.sourceforge.net/html/Home.html.

   Once the executable is available, run it with the following command, 
   >valgrind --dump-instr=yes --tool=callgrind ./vectorCopyMove 

   As a result a file "callgrind.out.XXXX" will be created. Now start this generated file with kcachegrind,

   >kcachegrind callgrind.out.XXXX
