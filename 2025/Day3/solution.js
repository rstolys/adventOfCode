/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 20 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let sumOfBatteries = 0; 
    for (let i = 0; i < data.length; i++)
        {
        let joltage = findMaxJoltage(data[i].toString(), 12);
        sumOfBatteries += joltage;
        }

    return sumOfBatteries;
    }

const MAX_JOLTAGE = 9;
function findMaxJoltage(batteryList, numBatteries)
    {
    let maxJoltage = "";
    let index = 0;
    for (let i = 0; i < numBatteries; i++)
        {
        let result = findNextBattery(batteryList, index, numBatteries - i - 1);
        index = result[0] + 1;
        maxJoltage = maxJoltage + "" + result[1];
        }

    return Number(maxJoltage);
    }


function findNextBattery(batteryList, startingIndex, remainingBatteries)
    {
    let i = 0;
    let num1 = 0;
    let num1Index = 0;
    for (let i = startingIndex; i < batteryList.length - remainingBatteries; i++)
        {
        if (batteryList[i] > num1)
            {
            num1 = batteryList[i];
            num1Index = i;
            }

        if (num1 == MAX_JOLTAGE)
            break;
        }

    return [num1Index, num1];
    }

function findMaxJoltagePart1(batteryList)
    {
    let i = 0;
    let num1 = 0;
    let num1Index = 0;
    for (; i < batteryList.length - 1; i++)
        {
        if (batteryList[i] > num1)
            {
            num1 = batteryList[i];
            num1Index = i;
            }

        if (num1 == MAX_JOLTAGE)
            break;
        }

    let num2 = 0;
    for (let j = num1Index + 1; j < batteryList.length; j++)
        {
        if (batteryList[j] > num2)
            num2 = batteryList[j];

        if (num2 == MAX_JOLTAGE)
            break;
        }

    return Number(num1 + "" + num2);
    }
    
module.exports.solution = solution;
