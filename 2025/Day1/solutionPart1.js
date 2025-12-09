/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 8 Dec 2025   Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/
// Check number of times we reached 0 at the end of a rotation
function solution(data)
    {
    let numTimesAt0 = 0;
    let index = 50; // Start the dial at 50
    for (var i = 0; i < data.length; i++)
        {
        let numMoves = getQuantity(data[i]);
        let moveUp = isRight(data[i]);
        for (var j = 0; j < numMoves; j++)
            index = moveDial(index, moveUp);

        if (index == 0)
            numTimesAt0++;
        }

    return numTimesAt0;
    }

function getQuantity(item)
    {
    return parseInt(item.slice(1));
    }

function isRight(item)
    {
    return item[0] == 'R';
    }

function moveDial(index, moveUp)
    {
    if (index == 99 && moveUp)
        return 0;
    else if (index == 0 && !moveUp)
        return 99;
    else if (moveUp)
        return index + 1;
    else
        return index - 1;
    }
    
module.exports.solution = solution;
