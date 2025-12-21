/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 20 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let gridValues = [];
    for (let i = 0; i < data.length; i++)
        gridValues.push(data[i].split(" ").filter(item => item.trim() != ""));

    let problems = [];
    let numProblems = gridValues[0].length;
    let numInputs = gridValues.length;
    for (let i = 0; i < numProblems; i++)
        {
        problems.push([]);
        for (let j = 0; j < numInputs; j++)
            problems[i].push(gridValues[j][i]);
        }

    let sumOfTotals = 0;
    for (let i = 0; i < problems.length; i++)
        sumOfTotals += solveProblem(problems[i]);

    return sumOfTotals;
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
