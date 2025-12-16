/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 15 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let totalButtonClicks = 0;
    for (let i = 0; i < data.length; i++)
        {
        let line = data[i];
        let parts = line.split(" ");
        parts.shift(); // We don't use this in part 2

        let finalState = ParseFinalState(parts.pop());
        let buttonPresses = ParseButtonPress(finalState.length, parts);

        let result = Solve(buttonPresses, finalState);

        console.log(`${i}. Button Clicks: ${result}`);
        // console.log(`${i}. Nodes: ${result.nodes.map(node => node.GetKey()).join(" -> ")}`);
        // console.log(`${i}. Path: ${result.path.map(path => ConvertButtonPress(path)).join(" -> ")}`);
        
        totalButtonClicks += result;
        }

    return totalButtonClicks;    
    }

// The problem can be modeled as a system of linear equations: Ax = b
// where A is the matrix of actions, x is the number of times each action is taken, and b is the target state.
// We can solve this using Gaussian Elimination.
function Solve(A, b)
    {
    let numRows = b.length;
    let numCols = A.length;

    // Build augmented matrix [A | b]
    let matrix = [];
    for (let r = 0; r < numRows; r++) 
        {
        let row = [];
        for (let c = 0; c < numCols; c++) 
            {
            row.push(A[c][r]);
            }
        row.push(b[r]);
        matrix.push(row);
        }

    // Gaussian Elimination to Reduced Row Echelon Form (RREF)
    let lead = 0;
    for (let r = 0; r < numRows; r++) 
        {
        if (numCols <= lead) 
            break;
        
        let i = r;
        while (Math.abs(matrix[i][lead]) < 1e-9) 
            {
            i++;
            if (numRows === i) 
                {
                i = r;
                lead++;
                if (numCols === lead) 
                    break;
                }
            }
        
        if (numCols === lead) break;

        // Swap rows
        let temp = matrix[i];
        matrix[i] = matrix[r];
        matrix[r] = temp;

        // Scale row to make pivot 1
        let val = matrix[r][lead];
        for (let j = 0; j < numCols + 1; j++) 
            {
            matrix[r][j] /= val;
            }

        // Eliminate other rows
        for (let i = 0; i < numRows; i++) 
            {
            if (i !== r) 
                {
                val = matrix[i][lead];
                for (let j = 0; j < numCols + 1; j++) 
                    {
                    matrix[i][j] -= val * matrix[r][j];
                    }
                }
            }
        lead++;
        }

    // Identify pivot columns and free columns
    let pivotCols = new Array(numRows).fill(-1);
    let isPivot = new Array(numCols).fill(false);
    
    for (let r = 0; r < numRows; r++) 
        {
        for (let c = 0; c < numCols; c++) 
            {
            if (Math.abs(matrix[r][c] - 1) < 1e-9) 
                {
                pivotCols[r] = c;
                isPivot[c] = true;
                break;
                }
            }
        }

    let freeCols = [];
    for (let c = 0; c < numCols; c++)
        {
        if (!isPivot[c]) freeCols.push(c);
        }

    let minTotalClicks = Infinity;
    let maxVal = Math.max(...b); // Safe upper bound for any single action

    // Recursive search for free variables
    function search(idx, currentX)
        {
        if (idx === freeCols.length)
            {
            // Calculate pivot variables based on current free variables
            let valid = true;
            let tempX = [...currentX];
            
            for (let r = 0; r < numRows; r++)
                {
                let pivot = pivotCols[r];
                if (pivot === -1) 
                    {
                    // Check for consistency: 0 = constant?
                    if (Math.abs(matrix[r][numCols]) > 1e-9)
                        {
                        valid = false;
                        break;
                        }
                    continue;
                    }

                // x_pivot = constant - sum(coeff * x_free)
                let val = matrix[r][numCols];
                for (let free of freeCols)
                    {
                    val -= matrix[r][free] * tempX[free];
                    }
                
                // Check if integer and non-negative
                if (val < -1e-9 || Math.abs(Math.round(val) - val) > 1e-9)
                    {
                    valid = false;
                    break;
                    }
                tempX[pivot] = Math.round(val);
                }

            if (valid)
                {
                let total = tempX.reduce((sum, v) => sum + v, 0);
                if (total < minTotalClicks) minTotalClicks = total;
                }
            return;
            }

        let col = freeCols[idx];
        
        // Calculate a tighter bound for this free variable
        // An action cannot be taken more times than the target value it contributes to
        let limit = maxVal;
        for(let r = 0; r < numRows; r++) 
            {
            if(A[col][r] > 0) 
                {
                limit = Math.min(limit, b[r]);
                }
            }

        // Try values for this free variable
        for (let v = 0; v <= limit; v++)
            {
            currentX[col] = v;
            search(idx + 1, currentX);
            }
        }

    let initialX = new Array(numCols).fill(0);
    search(0, initialX);

    return minTotalClicks === Infinity ? 0 : minTotalClicks;
    }

// Convert the button pressed into path traversals
function ParseButtonPress(numButtons, buttonPresses)
    {
    let paths = [];
    for (let press of buttonPresses)
        {
        let trimmed = press.slice(1, -1);
        let buttonsPressed = trimmed.split(",").map(Number);
        let path = Array(numButtons).fill(0);
        for (let button of buttonsPressed)
            path[button] = 1;

        paths.push(path);
        }

    return paths;
    }

// Convert the array representation of button press into a string
function ConvertButtonPress(path)
    {
    let button = "(";
    for (let i = 0; i < path.length; i++)
        {
        if (path[i] == 1)
            button += i + ",";
        }

    button = button.slice(0, -1) + ")";
    return button;
    }

// Convert the final state into a data point on a graph
function ParseFinalState(input)
    {
    // Remove the first and last characters
    let trimmed = input.slice(1, -1);
    
    // Convert to data point
    return trimmed.split(",").map(Number);
    }
    
module.exports.solution = solution;
