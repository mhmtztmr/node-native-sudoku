# node-native-sudoku

This is a native Node.js module written in C++ in order to solve Sudoku puzzles using Depth-first Search Algorithm.

## Install

`npm -i node-native-sudoku`

## Example Usage

```
var input = [
    [0, 5, 7, 0, 6, 0, 2, 0, 0],
    [8, 0, 2, 0, 0, 0, 0, 1, 6],
    [0, 0, 0, 0, 0, 2, 0, 0, 0],
    [0, 0, 0, 2, 0, 5, 0, 7, 4],
    [7, 4, 0, 0, 0, 0, 0, 0, 0],
    [0, 8, 1, 4, 9, 0, 0, 0, 0],
    [6, 0, 3, 8, 5, 0, 0, 0, 7],
    [1, 0, 0, 9, 0, 0, 0, 4, 3],
    [0, 0, 0, 3, 0, 0, 0, 0, 2]
];

var output = sudoku.solve(input);

/*

Returns the following:

[
    [4, 5, 7, 1, 6, 8, 2, 3, 9],
    [8, 3, 2, 5, 4, 9, 7, 1, 6],
    [9, 1, 6, 7, 3, 2, 4, 5, 8],
    [3, 6, 9, 2, 1, 5, 8, 7, 4],
    [7, 4, 5, 6, 8, 3, 9, 2, 1],
    [2, 8, 1, 4, 9, 7, 3, 6, 5],
    [6, 2, 3, 8, 5, 4, 1, 9, 7],
    [1, 7, 8, 9, 2, 6, 5, 4, 3],
    [5, 9, 4, 3, 7, 1, 6, 8, 2]
];
*/
```
