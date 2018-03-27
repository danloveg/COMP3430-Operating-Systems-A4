# Memory Management and Persistent Storage in C
### COMP3430 Winter 2018 Assignment 4

## Overview

The amount of code for this assignment is minimal, most of the questions are written answers. The code that was written for Question 1 demostrates free space amalgamation, an algorithm for combining adjacent pieces of freed memory to avoid fragmentation. The rest of the questions are on paged memory systems (Q2) and filesystems (Q3).

## Details
All of the code has only been tested on Linux (Scientific and Ubuntu) and cannot be guaranteed to work on Mac or Windows. The assignment questions that are not in code are in the PDF file `COMP3430A4LovegroveDaniel.pdf`.

## Running the Code

### Question 1

Running the code for Q1 applies unit tests to the memory manager written in `mymem.c`. Using a terminal, descend into the Q1 folder: `cd Q1`. Make the executable: `make`. Run the tests: `./memTest`. All of the tests should print out a PASS message.
