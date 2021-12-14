/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * ?? Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    var poly = data[0];
    // Remove first two elements
    data.shift();
    data.shift();

    var dict = createDict(data);
    var lPairs = createLetterPairs(poly);

    //console.log(lPairs);

    for (var s = 0; s < 40; s++)
        {
        lPairs = applyStep(lPairs, dict);
        }

    //console.log(lPairs);

    return findAns(lPairs, poly);
    }

function findAns(lPairs, poly)
    {
    var lCount = [];

    for (var c = 0; c < lPairs.length; c++)
        {
        var currentLetter = lPairs[c].pair[0];
        var index = getLcountIndex(lCount, currentLetter);
        if (index != -1)
            {
            lCount[index].count += lPairs[c].count;
            }
        else 
            {
            lCount.push({letter: currentLetter, count: lPairs[c].count});
            }
        }

    // Add last letter
    var index = getLcountIndex(lCount, poly[poly.length - 1]);
    if (index != -1)
        {
        lCount[index].count += 1;
        }
    else 
        {
        lCount.push({letter: currentLetter, count: 1});
        }

    console.log(lCount);
    
    var max = lCount[0].count;
    var min = lCount[0].count;
    for (var c = 0; c < lCount.length; c++)
        {
        if (lCount[c].count > max)
            max = lCount[c].count;

        if (lCount[c].count < min)
            min = lCount[c].count;
        }

    return max - min;
    }

function getLcountIndex(lCount, l)
    {
    var index = -1;
    for (var i = 0; i < lCount.length; i++)
        {
        if (l == lCount[i].letter)
            {
            index = i;
            break;
            }
        }

    return index;
    }

function createLetterPairs(poly)
    {
    var lPairs = [];
    for (var c = 1; c < poly.length; c++)
        {
        var pair = poly[c-1] + poly[c];
        lPairs.push({pair: pair, count: 1});
        }

    return lPairs;
    }

function applyStep(lPairs, dict)
    {
    var newLPairs = [];
    for (var p = 0; p < lPairs.length; p++)
        {
        var fChar = lPairs[p].pair[0];
        var sChar = lPairs[p].pair[1];
        var index = getIndex(fChar + sChar, dict);
        if (index != -1)
            {
            var pair1 = fChar + dict[index].value;
            var p1Index = getPairIndex(newLPairs, pair1);
            if (p1Index != -1)
                newLPairs[p1Index].count += lPairs[p].count;
            else
                newLPairs.push({pair: pair1, count: lPairs[p].count});


            var pair2 = dict[index].value + sChar;
            var p2Index = getPairIndex(newLPairs, pair2);
            if (p2Index != -1)
                newLPairs[p2Index].count += lPairs[p].count;
            else
                newLPairs.push({pair: pair2, count: lPairs[p].count});
            }
        else 
            {
            console.log("Does this happen?");
            newLPairs.push(lPairs[p]);
            }
        }

    return newLPairs;
    }

function getPairIndex(lPairs, pair)
    {
    var index = -1;
    for (var i = 0; i < lPairs.length; i++)
        {
        if (pair == lPairs[i].pair)
            {
            index = i;
            break;
            }
        }
    
    return index;
    }

function getIndex(key, dict)
    {
    var index = -1;
    for (var i = 0; i < dict.length; i++)
        {
        if (key == dict[i].key)
            {
            index = i;
            break;
            }
        }
    
    return index;
    }

function createDict(input)
    {
    var dict = [];

    for (var i = 0; i < input.length; i++)
        {
        var line = input[i].split(" -> ");
        var d = {key: line[0], value: line[1]};
        dict.push(d);
        }
    
    return dict;
    }
    
module.exports.solution = solution;
