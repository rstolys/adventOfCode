/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 20 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let grid = [];
    for (let i = 0; i < data.length; i++)
        {
        grid.push([]);
        for (let j = 0; j < data[i].length; j++)
            grid[i].push(data[i][j]);
        }

    let totalAvailableRolls = 0;
    let availableRolls = 0;
    let iteration = 0;
    do
        {
        iteration++;
        availableRolls = 0;
        for (let i = 0; i < grid.length; i++)
            {
            for (let j = 0; j < grid[i].length; j++)
                {
                if (!isRollOnGridAt(grid, i, j))
                    continue;

                let isAvailable = isRollAvailable(grid, i, j);
                availableRolls += isAvailable ? 1 : 0;
                }
            }

        totalAvailableRolls += availableRolls;
        //console.log(availableRolls);
        }
    while (availableRolls > 0 && iteration < 1000);

    return totalAvailableRolls;
    }

const ROLL = '@';
function isRollAvailable(grid, i, j)
    {
    let rollsNearby = 0;

    rollsNearby += isRollOnGridAt(grid, i - 1, j - 1);
    rollsNearby += isRollOnGridAt(grid, i - 1, j);
    rollsNearby += isRollOnGridAt(grid, i - 1, j + 1);
    rollsNearby += isRollOnGridAt(grid, i, j - 1);
    rollsNearby += isRollOnGridAt(grid, i, j + 1);
    rollsNearby += isRollOnGridAt(grid, i + 1, j - 1);
    rollsNearby += isRollOnGridAt(grid, i + 1, j);
    rollsNearby += isRollOnGridAt(grid, i + 1, j + 1);

    let isAvailable = rollsNearby < 4;
    if (isAvailable)
        grid[i][j] = 'x'; // Remove the roll

    return isAvailable;
    }

function isRollOnGridAt(grid, i, j)
    {
    if (i < 0 || i >= grid.length)
        return false;
    else if (j < 0 || j >= grid[i].length)
        return false;

    return (grid[i][j] == ROLL) ? 1 : 0;
    }
    
module.exports.solution = solution;
