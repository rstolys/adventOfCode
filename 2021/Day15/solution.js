/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * ?? Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/
var dimension = -1;
var nodesVisited = 0;

function solution(data)
    {
    var grid = convertInputToGrid(data);
    dimension = grid.length;

    grid = multiplyGridBy5(grid);

    console.log("Finding Node Costs");
    grid = findNodeCosts(grid, dimension*5);

    return grid[dimension*5 -1][dimension*5 -1].dist;
    }

function findNodeCosts(grid, dim)
    {
    var q = [];

    // Fill Queue and dist array
    for(var r = 0; r < grid.length; r++)
        {
        for (var c = 0; c < grid[r].length; c++)
            {
            q.push(grid[r][c]);
            }
        }
        
    grid[0][0].dist = 0;

    while (stillNodesToVisit(grid))
        {
        ++nodesVisited;
        console.log(nodesVisited);
        var [r, c] = minDistance(grid);
        grid[r][c].visited = true;

        if (r != 0) // Can we go up
            {
            var newDist = Number(grid[r][c].dist) + Number(grid[r-1][c].value);
            var currentDist = grid[r-1][c].dist;
            grid[r-1][c].dist = newDist < currentDist ? newDist : currentDist;
            }

        if (r != dim - 1) // Can we go down
            {
            var newDist = Number(grid[r][c].dist) + Number(grid[r+1][c].value);
            var currentDist = grid[r+1][c].dist;
            grid[r+1][c].dist = newDist < currentDist ? newDist : currentDist;
            }
            
        if (c != 0) // Can we go left
            {
            var newDist = Number(grid[r][c].dist) + Number(grid[r][c-1].value);
            var currentDist = grid[r][c-1].dist;
            grid[r][c-1].dist = newDist < currentDist ? newDist : currentDist;
            }
            
        if (c != dim - 1) // Can we go right
            {
            var newDist = Number(grid[r][c].dist) + Number(grid[r][c+1].value);
            var currentDist = grid[r][c+1].dist;
            grid[r][c+1].dist = newDist < currentDist ? newDist : currentDist;
            }
        }

    return grid;
    }

function stillNodesToVisit(grid)
    {
    var stillNodesToVisit = false;

    for(var r = 0; r < grid.length; r++)
        {
        for (var c = 0; c < grid[r].length; c++)
            {
            if (!grid[r][c].visited)
                {
                stillNodesToVisit = true;
                break;
                }
            }
        }

    return stillNodesToVisit;
    }

function minDistance(grid)
    { 
    var min = Number.MAX_VALUE;
    var minRow = -1;
    var minCol = -1;

    for(var r = 0; r < grid.length; r++)
        {
        for (var c = 0; c < grid[r].length; c++)
            {
            if (!grid[r][c].visited && grid[r][c].dist <= min)
                {
                min = grid[r][c].dist;
                minRow = r;
                minCol = c;
                }
            }
        }

    return [minRow, minCol];
    }
    
function multiplyGridBy5(grid)
    {
    var newGrid = [];

    for(var r = 0; r < grid.length * 5; r++)
        {
        var row = [];
        for (var c = 0; c < grid[r%dimension].length * 5; c++)
            {
            if (r < dimension && c < dimension)
                row.push(grid[r][c]);
            else 
                {
                var gridTile = {value: grid[r%dimension][c%dimension].value, dist: Number.MAX_VALUE, visited: false};
                var newValue = (gridTile.value + Math.floor(r / dimension) + Math.floor(c / dimension));
                if (newValue > 9)
                    newValue = newValue % 10 + 1;
                
                gridTile.value = newValue;
                row.push(gridTile);
                }
            }

        newGrid.push(row);
        }

    return newGrid;
    }


// {value: #, dist: #, visited: false}
function convertInputToGrid(data)
    {
    var grid = [];

    for(var r = 0; r < data.length; r++)
        {
        var row = [];
        for (var c = 0; c < data[r].length; c++)
            {
            row.push({value: Number(data[r][c]), dist: Number.MAX_VALUE, visited: false});
            }

        grid.push(row);
        }

    return grid
    }

    
module.exports.solution = solution;
