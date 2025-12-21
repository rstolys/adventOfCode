/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 20 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let problems = [];
    let numProblems = data[0].split(" ").filter(item => item.trim() != "").length;
    let numInputs = data.length;
    let operationsRow = data[data.length - 1].split("");
    let subStringStart = 0;
    for (let i = 0; i < numProblems; i++)
        {
        problems.push([]);

        // Find the widgth of the problem
        let nextProblemIndexStart = findNextProblemStart(operationsRow, subStringStart);
        let problemWidth = nextProblemIndexStart - subStringStart - 1;
        let inputs = [];

        // When we are dealing with the last problem, we can't rely on the 
        if (i == numProblems - 1)
            {
            for (let j = 0; j < numInputs - 1; j++)
                inputs.push(data[j].substring(subStringStart));
            
            problemWidth = inputs[0].length;
            }
        else
            {
            for (let j = 0; j < numInputs - 1; j++)
                inputs.push(data[j].substring(subStringStart, subStringStart + problemWidth));
            }

        let operation = data[numInputs - 1][subStringStart];

        // Convert the problem inputs to odd format
        for (let c = problemWidth - 1; c >= 0; c--)
            {
            let value = "";
            for (let r = 0; r < inputs.length; r++)
                if (inputs[r][c] != "")
                    value = value + "" + inputs[r][c];

            problems[i].push(Number(value));
            }

        problems[i].push(operation);

        subStringStart = nextProblemIndexStart;
        }

    let sumOfTotals = 0;
    for (let i = 0; i < problems.length; i++)
        sumOfTotals += solveProblem(problems[i]);

    return sumOfTotals;
    }

function findNextProblemStart(operationRow, startingIndex)
    {
    let width = 1;
    for (let i = startingIndex + 1; i < operationRow.length; i++)
        {
        if (operationRow[i] != " ")
            break;

        width++
        }

    return startingIndex + width;
    }

function solveProblem(problemInputs)
    {
    let isAdd = problemInputs[problemInputs.length - 1] == "+";
    let total = isAdd ? 0 : 1;
    
    for (let i = 0; i < problemInputs.length - 1; i++)
        total = isAdd ? total + Number(problemInputs[i]) : total * Number(problemInputs[i]);

    return total;
    }
    
module.exports.solution = solution;
