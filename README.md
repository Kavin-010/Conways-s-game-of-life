# Conway's game of life(C++)

This is a simple C++ implementation of Conway's Game of Life, a cellular automaton. It simulates a grid of cells that evolve based on simple rules. The game runs in the console using ASCII characters.

## How It Works


The grid has cells that can either be alive or dead.

## The state of the cells changes each generation based on these rules:**

A live cell with fewer than two neighbors dies (underpopulation).

A live cell with two or three neighbors stays alive.

A live cell with more than three neighbors dies (overpopulation).

A dead cell with exactly three neighbors becomes alive (reproduction).
