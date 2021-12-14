/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 13 Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

const FILLED = "X";
const EMPTY = "."

function solution(data)
    {
    var points = generatePointsAndFolds(data, true);
    var folds = generatePointsAndFolds(data, false);

    var grid = convertToGrid(points);

    for (var f = 0; f < folds.length; f++)
        {
        grid = executeFold(folds[f], grid);
        }

    printGrid(grid);

    return countVisibleDots(grid);
    }

function countVisibleDots(grid)
    {
    var count = 0;

    for(var r = 0; r < grid.length; r++)
        {
        for (var c = 0; c < grid[r].length; c++)
            {
            if (grid[r][c] == FILLED)
                count++;
            }
        }

    return count;
    }

function executeFold(fold, grid)
    {
    var instr = fold.slice(11); //fold along 
    var yOrx = instr.split("=")[0];
    var loc = instr.split("=")[1];

    var newGrid = [];

    // Create new grid shape
    for(var r = 0; r < grid.length; r++)
        {
        var newRow = [];
        for (var c = 0; c < grid[r].length; c++)
            {
            if (c < loc && yOrx == "x")
                {
                newRow.push(grid[r][c]);
                continue;
                }
            else if (r < loc && yOrx == "y")
                {
                newRow.push(grid[r][c]);
                continue;
                }
            }
        newGrid.push(newRow);
        }

    // Add folded over pieces
    for(var r = 0; r < grid.length; r++)
        {
        for (var c = 0; c < grid[r].length; c++)
            {
            if (c >= loc && yOrx == "x" && grid[r][c] == FILLED)
                newGrid[r][loc - (c - loc)] = grid[r][c];
            else if (r >= loc && yOrx == "y" && grid[r][c] == FILLED)
                newGrid[loc - (r - loc)][c] = grid[r][c];
            }
        }

    return newGrid;
    }

function printGrid(grid)
    {
    for(var r = 0; r < grid.length; r++)
        {
        var row = "";
        for (var c = 0; c < grid[r].length; c++)
            {
            row += grid[r][c] + " ";
            }
        console.log(row);
        }
    }

function convertToGrid(points)
    {
    var coordinates = [];
    var maxX = 0;
    var maxY = 0;

    points.forEach(point =>
        {
        var xy = point.split(",");
        var x = Number(xy[0]);
        var y = Number(xy[1]);

        if (x > maxX)
            maxX = x;

        if (y > maxY)
            maxY = y;

        coordinates.push({x: x, y: y});
        })

    var cords = [];
    for (var r = 0; r <= maxY; r++)
        {
        var newRow = [];
        for (var c = 0; c <= maxX; c++)
            {
            if (coordinates.find(item => item.x == c && item.y == r) != undefined)
                newRow.push(FILLED);
            else 
                newRow.push(EMPTY);
            }
        cords.push(newRow);
        }

    return cords;
    }

function generatePointsAndFolds(data, getPoints)
    {
    var endOfPoints = false;
    var points = [];
    var folds = [];
    data.forEach(element => 
        {
        if (element == "")
            {
            endOfPoints = true;
            return;
            }

        if (endOfPoints)
            folds.push(element);
        else 
            points.push(element);
        });

    // console.log(points);
    // console.log(folds);

    if (getPoints)
        return points;
    else 
        return folds;
    }

module.exports.solution = solution;
