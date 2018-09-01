var sudoku = require('../index');
var assert = require("chai").assert;

describe("sudoku.solve()", function () {
    it('should solve sudoku if input valid', function () {
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
        var expected = [
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
        var actual = sudoku.solve(input);
        assert.deepEqual(actual, expected);
    });

    it('should return undefined if input invalid', function () {
        var input = [
            [5, 5, 7, 0, 6, 0, 2, 0, 0],
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
        assert.notExists(output);
    });
});