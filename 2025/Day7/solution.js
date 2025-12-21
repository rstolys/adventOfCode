/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 21 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

const START = "S";
function solution(data)
    {
    let grid = [];
    let startCell = [];
    for (let i = 0; i < data.length; i++)
        {
        grid.push([]);
        let rowData = data[i].split("");
        for (let j = 0; j < rowData.length; j++)
            {
            grid[i].push(rowData[j]);
            if (rowData[j] == START)
                startCell = [i, j];
            } 
        }

    //return countBeamsSplit(grid, startCell[0] + 1, startCell[1]); // Part 1
    return countBeamsPaths(grid, startCell[0] + 1, startCell[1]) + 1; // Part 2
    }

const SPLIT = "^";
var found = {};
function countBeamsPaths(grid, locI, locJ)
    {
    if (locI < 0 || locI >= grid.length)
        return 0;
    else if (locJ < 0 || locJ >= grid[0].length)
        return 0; 

    // Check if we have visited so we don't double count
    let cellId = `${locI}-${locJ}`;
    if (found[cellId])
        return found[cellId];

    let beamPaths = 0;

    let cell = grid[locI][locJ];
    if (cell == SPLIT)
        beamPaths = countBeamsPaths(grid, locI, locJ + 1) + countBeamsPaths(grid, locI, locJ - 1) + 1;
    else 
        beamPaths = countBeamsPaths(grid, locI + 1, locJ);

    // record the number of paths travelled for others
    found[cellId] = beamPaths;

    return beamPaths;
    }

var visited = {};
function countBeamsSplit(grid, locI, locJ)
    {
    if (locI < 0 || locI >= grid.length)
        return 0;
    else if (locJ < 0 || locJ >= grid[0].length)
        return 0; 

    // Check if we have visited so we don't double count
    let cellId = `${locI}-${locJ}`;
    if (visited[cellId])
        return 0;

    // If we have not, mark as visited and count splits from here
    visited[cellId] = true;

    let cell = grid[locI][locJ];
    if (cell == SPLIT)
        return countBeamsSplit(grid, locI, locJ + 1) + countBeamsSplit(grid, locI, locJ - 1) + 1;
    else 
        return countBeamsSplit(grid, locI + 1, locJ);
    }
    
module.exports.solution = solution;
