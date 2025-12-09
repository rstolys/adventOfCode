/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 09 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/
class Tile
    {
    constructor(coordinate, color = "white")
        {
        let [x, y] = coordinate.split(',').map(Number);
        this.x = x;
        this.y = y;
        this.color = color;
        }
    }

class Grid
    {
    grid = [[]];
    constructor(largestX, largestY)
        {
        for (let i = 0; i <= largestY; i++)
            {
            this.grid[i] = [];
            for (let j = 0; j <= largestX; j++)
                this.grid[i][j] = new Tile(`${j},${i}`, "white");
            }
        }

    setTiles(tile, previousTile)
        {
        // Make allt tiles between the two, green
        // We know they will share either an x or y coordinate
        if (tile.x == previousTile.x)
            {
            for (let i = Math.min(tile.y, previousTile.y); i <= Math.max(tile.y, previousTile.y); i++)
                this.grid[tile.y][i] = new Tile(`${tile.x},${i}`, "green");
            }
        else 
            {
            for (let i = Math.min(tile.x, previousTile.x); i <= Math.max(tile.x, previousTile.x); i++)
                this.grid[tile.y][i] = new Tile(`${i},${tile.y}`, "green");
            }

        // Ensure we didn't overwrite the red tiles
        this.grid[tile.y][tile.x] = tile;
        this.grid[previousTile.y][previousTile.x] = previousTile;
        }

    areTilesBetweenGreenOrRed(tile1, tile2)
        {
        let areAllGreenOrRed = true;

        // Check in the 
        for (let i = Math.min(tile1.x, tile2.x); i <= Math.max(tile1.x, tile2.x); i++)
            for (let j = Math.min(tile1.y, tile2.y); j <= Math.max(tile1.y, tile2.y); j++)
                areAllGreenOrRed = areAllGreenOrRed && (this.grid[j][i].color == "green" || this.grid[j][i].color == "red");

        return areAllGreenOrRed;
        }
    }

function solution(data)
    {
    let redTiles = [];
    let smallestX = Infinity;
    let smallestY = Infinity;
    let largestX = -Infinity;
    let largestY = -Infinity;
    for (let line of data)
        {
        let tile = new Tile(line, "red");
        if (tile.x < smallestX) smallestX = tile.x;
        if (tile.y < smallestY) smallestY = tile.y;
        if (tile.x > largestX) largestX = tile.x;
        if (tile.y > largestY) largestY = tile.y;
        redTiles.push(tile);
        }

    // Build a grid with red and green tiles
    let grid = new Grid(largestX, largestY);
    for (let i = 0; i < redTiles.length; i++)
        grid.setTiles(redTiles[i], i == 0 ? redTiles[redTiles.length - 1] : redTiles[i - 1]);
        

    let maxArea = 0;
    for (let i = 0; i < redTiles.length; i++)
        {
        for (let j = 0; j < redTiles.length; j++)
            {
            if (grid.areTilesBetweenGreenOrRed(redTiles[i], redTiles[j]))
                {
                let area = Math.abs((redTiles[i].x - redTiles[j].x + 1) * (redTiles[i].y - redTiles[j].y + 1));
                if (area > maxArea)
                    maxArea = area;
                }
            }
        }

    return maxArea;
    }
    
module.exports.solution = solution;
