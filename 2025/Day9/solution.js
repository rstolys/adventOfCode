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
    constructor()
        {
        this.grid = {};
        }

    setTiles(tile, previousTile)
        {
        // Make all tiles between the two, green
        // We know they will share either an x or y coordinate
        // While doing this, we will also set the tiles outside of the box to be an error colour for our solution
        if (tile.x == previousTile.x)
            {
            for (let i = Math.min(tile.y, previousTile.y); i <= Math.max(tile.y, previousTile.y); i++)
                this.grid[tile.x][i] = "green";
            }
        else // They have the same y value
            {
            for (let i = Math.min(tile.x, previousTile.x); i <= Math.max(tile.x, previousTile.x); i++)
                this.grid[i][tile.y] = "green";
            }

        // Ensure we didn't overwrite the red tiles
        this.grid[tile.x][tile.y] = "red";
        this.grid[previousTile.x][previousTile.y] = "red";
        }

    createBoxBoundary(startingTile)
        {
        
        }

    // If this is a valid box, then when tracing the outsides of the box, we will never cross red/green tile line
    // To keep track of this we should mark that we are currently on the edge of the box
    // If we touch move inside the box, then we mark that we are inside, if we find we are outside, then we know this is invalid
    isValidBox(tile1, tile2)
        {
        let isValid = true;

        let onEdge = true;
        let onInside = false;

        // Start by going down the left side 
        for (let i = Math.min(tile1.x, tile2.x); i <= Math.max(tile1.x, tile2.x); i++)
            {
            if (this.grid[i][Math.min(tile1.y, tile2.y)].color == "white")
            }
            isValid

        for (let i = Math.min(tile1.x, tile2.x); i <= Math.max(tile1.x, tile2.x); i++)
            for (let j = Math.min(tile1.y, tile2.y); j <= Math.max(tile1.y, tile2.y); j++)
                areAllGreenOrRed = areAllGreenOrRed && (this.grid[i][j].color == "green" || this.grid[i][j].color == "red");

        return areAllGreenOrRed;
        }
    }

function solution(data)
    {
    let redTiles = [];
    for (let line of data)
        redTiles.push(new Tile(line, "red"));

    // Build a grid with red and green tiles
    let grid = new Grid(largestX, largestY);
    for (let i = 0; i < redTiles.length; i++)
        grid.setTiles(redTiles[i], i == 0 ? redTiles[redTiles.length - 1] : redTiles[i - 1]);

    grid.fillInsideOfRedAndGreenTiles();

    let maxArea = 0;
    for (let i = 0; i < redTiles.length; i++)
        {
        for (let j = 0; j < redTiles.length; j++)
            {
            let area = Math.abs((redTiles[i].x - redTiles[j].x + 1) * (redTiles[i].y - redTiles[j].y + 1));
            if (grid.areTilesBetweenGreenOrRed(redTiles[i], redTiles[j]))
                {
                //let area = Math.abs((redTiles[i].x - redTiles[j].x + 1) * (redTiles[i].y - redTiles[j].y + 1));
                if (area > maxArea)
                    maxArea = area;
                }
            else 
                {
                console.log(area);
                }
            }
        }

    return maxArea;
    }
    
module.exports.solution = solution;
