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
    grid = [];
    constructor(largestX, largestY)
        {
        this.grid = [];
        for (let i = 0; i <= largestX + 1; i++)
            {
            this.grid.push([]);
            for (let j = 0; j <= largestY + 1; j++)
                this.grid[i][j] = new Tile(`${i},${j}`, "white");
            }
        }

    setTiles(tile, previousTile)
        {
        // Make allt tiles between the two, green
        // We know they will share either an x or y coordinate
        if (tile.x == previousTile.x)
            {
            for (let i = Math.min(tile.y, previousTile.y); i <= Math.max(tile.y, previousTile.y); i++)
                this.grid[tile.x][i] = new Tile(`${tile.x},${i}`, "green");
            }
        else // They have the same y value
            {
            for (let i = Math.min(tile.x, previousTile.x); i <= Math.max(tile.x, previousTile.x); i++)
                this.grid[i][tile.y] = new Tile(`${i},${tile.y}`, "green");
            }

        // Ensure we didn't overwrite the red tiles
        this.grid[tile.x][tile.y] = tile;
        this.grid[previousTile.x][previousTile.y] = previousTile;
        }

    fillInsideOfRedAndGreenTiles()
        {
        // Fill only the interior: mark all "outside" reachable tiles first,
        // then turn remaining enclosed white tiles to green.
        const rows = this.grid.length;
        const cols = this.grid[0].length;

        // Track tiles that are reachable from the grid boundary without crossing red/green
        const outside = new Set();
        const enqueueIfOutside = (x, y, queue) => {
            if (x < 0 || x >= rows || y < 0 || y >= cols) return;
            const key = `${x},${y}`;
            if (outside.has(key)) return;
            const color = this.grid[x][y].color;
            // Borders (red/green) block; only traverse through white
            if (color === "red" || color === "green") return;
            outside.add(key);
            queue.push(new Tile(key));
        };

        // BFS from every boundary cell
        let queue = [];
        // Top and bottom rows
        for (let y = 0; y < cols; y++)
            {
            enqueueIfOutside(0, y, queue);
            enqueueIfOutside(rows - 1, y, queue);
            }
        // Left and right columns
        for (let x = 0; x < rows; x++)
            {
            enqueueIfOutside(x, 0, queue);
            enqueueIfOutside(x, cols - 1, queue);
            }

        while (queue.length)
            {
            const current = queue.shift();
            const { x, y } = current;
            // Explore 4-neighbors
            enqueueIfOutside(x - 1, y, queue);
            enqueueIfOutside(x + 1, y, queue);
            enqueueIfOutside(x, y - 1, queue);
            enqueueIfOutside(x, y + 1, queue);
            }

        // Any white tile not marked as outside and not a red border is interior
        for (let x = 0; x < rows; x++)
            for (let y = 0; y < cols; y++)
                {
                const key = `${x},${y}`;
                const color = this.grid[x][y].color;
                if (color === "white" && !outside.has(key))
                    this.grid[x][y].color = "green";
                }
        }

    areTilesBetweenGreenOrRed(tile1, tile2)
        {
        let areAllGreenOrRed = true;

        // Check in the 
        for (let i = Math.min(tile1.x, tile2.x); i <= Math.max(tile1.x, tile2.x); i++)
            for (let j = Math.min(tile1.y, tile2.y); j <= Math.max(tile1.y, tile2.y); j++)
                areAllGreenOrRed = areAllGreenOrRed && (this.grid[i][j].color == "green" || this.grid[i][j].color == "red");

        return areAllGreenOrRed;
        }
    }

function solution(data)
    {
    let redTiles = [];
    let largestX = -Infinity;
    let largestY = -Infinity;
    for (let line of data)
        {
        let tile = new Tile(line, "red");

        if (tile.x > largestX) largestX = tile.x;
        if (tile.y > largestY) largestY = tile.y;

        redTiles.push(tile);
        }

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
