/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 08 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let items = data[0].split(',');
    let duplicatedItems = [];
    for (let i = 0; i < items.length; i++)
        {
        let range = items[i].split('-').map(Number);
        for (let j = range[0]; j <= range[1]; j++)
            {
            // if (hasDuplicatePart1(j))
            //     duplicatedItems.push(j);
        
            if (hasDuplicatePart2(j))
                duplicatedItems.push(j);
            }
        }

    duplicatedItems = duplicatedItems.sort((a, b) => a - b);
    return sumValues(duplicatedItems);
    }

function sumValues(arr)
    {
    let sum = 0;
    for (let i = 0; i < arr.length; i++)
        {
        sum += Number(arr[i]);
        }

    return sum;
    }

function hasDuplicatePart2(number)
    {
    let numStr = number.toString();
    let isDuplicate = false;

    // We need to check for duplicates of any length (e.g. 123123123 is now considered a duplicate)
    for (let len = 1; len <= Math.floor(numStr.length / 2); len++)
        {
        if (numStr.length % len != 0)
            continue;

        isDuplicate = true;
        let comparePart = numStr.substring(0, len);
        for (let p = 1; p * len < numStr.length; p++)
            {
            let testPart = numStr.substring(p*len, p*len + len);
            if (testPart != comparePart)
                {
                isDuplicate = false;
                break;
                }
            }

        if (isDuplicate)
            break;
        }

    return isDuplicate;
    }

function hasDuplicatePart1(number)
    {
    let numStr = number.toString();
    if (numStr.length % 2 == 1)
        return false;

    let half = numStr.length / 2;
    let firstHalf = numStr.substring(0, half);
    let secondHalf = numStr.substring(half);
    
    return firstHalf === secondHalf;
    }
    
module.exports.solution = solution;
