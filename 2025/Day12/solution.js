/*-----------------------------------------------------------------------------
 * solution.js
 *
 * ?? Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/
class Present
    {
    constructor(type, lines)
        {
        this.Type = type;
        this.Shape = [];
        for (let line of lines)
            this.Shape.push(line.split('').map(char => char === '#' ? 1 : 0));

        // Compute Rotations, keep only unique ones
        this.Rotations = [];
        let currentShape = this.Shape;
        for (let i = 0; i < 4; i++)
            {
            // Check if this rotation is unique
            let isUnique = true;
            for (let existingShape of this.Rotations)
                {
                let shapesAreSame = true;
                if (existingShape.length === currentShape.length && existingShape[0].length === currentShape[0].length)
                    {
                    for (let r = 0; r < existingShape.length; r++)
                        for (let c = 0; c < existingShape[0].length; c++)
                            {
                            if (existingShape[r][c] !== currentShape[r][c])
                                {
                                shapesAreSame = false;
                                break;
                                }
                            if (!shapesAreSame)
                                break;
                            }
                    }
                else
                    shapesAreSame = false;

                if (shapesAreSame)
                    {
                    isUnique = false;
                    break;
                    }
                }

            if (isUnique)
                this.Rotations.push(currentShape);

            // Rotate 90 degrees clockwise for next iteration
            let newShape = [];
            let rows = currentShape.length;
            let cols = currentShape[0].length;
            for (let c = 0; c < cols; c++)
                {
                let newRow = [];
                for (let r = rows - 1; r >= 0; r--)
                    newRow.push(currentShape[r][c]);
                newShape.push(newRow);
                }
            currentShape = newShape;
            }
        }

    GetArea()
        {
        let area = 0;
        for (let row of this.Shape)
            for (let cell of row)
                area += cell;
            
        return area;
        }
    }

class Trees
    {
    constructor(line, presents)
        {
        let parts = line.split(':');
        this.Height = parts[0].split('x')[0];
        this.Width = parts[0].split('x')[1];

        let numOfEachType = parts[1].split(' ').filter(part => part.trim() !== '');
        this.Type0 = numOfEachType[0];
        this.Type1 = numOfEachType[1];
        this.Type2 = numOfEachType[2];
        this.Type3 = numOfEachType[3];
        this.Type4 = numOfEachType[4];
        this.Type5 = numOfEachType[5];

        this.Presents = presents;
        }

    DoPresentsFit()
        {
        // Lets do some basic checks first 
        let totalAvailableArea = this.Height * this.Width;

        let totalRequiredArea = 0;
        totalRequiredArea += this.Presents.filter(p => p.Type == 0)[0].GetArea() * this.Type0;
        totalRequiredArea += this.Presents.filter(p => p.Type == 1)[0].GetArea() * this.Type1;
        totalRequiredArea += this.Presents.filter(p => p.Type == 2)[0].GetArea() * this.Type2;
        totalRequiredArea += this.Presents.filter(p => p.Type == 3)[0].GetArea() * this.Type3;
        totalRequiredArea += this.Presents.filter(p => p.Type == 4)[0].GetArea() * this.Type4;
        totalRequiredArea += this.Presents.filter(p => p.Type == 5)[0].GetArea() * this.Type5;

        return totalRequiredArea <= totalAvailableArea;
        }
    }

function solution(data)
    {
    let presents = [];
    for (let i = 0; i <= 5; i++)
        presents.push(new Present(Number(data[i*5].split('')[0]), [data[i*5 + 1], data[i*5 + 2], data[i*5 + 3]]));

    let trees = [];
    for (let i = 30; i < data.length; i++)
        trees.push(new Trees(data[i], presents));

    return trees.map(tree => tree.DoPresentsFit()).length;
    }
    
module.exports.solution = solution;
