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
        let range = items[i].split('-');
        for (let j = range[0]; j <= range[1]; j++)
            {
            if (hasDuplicate(j))
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

function hasDuplicate(number)
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
