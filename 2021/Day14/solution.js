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

    for (var s = 0; s < 10; s++)
        {
        lPairs = applyStep(lPairs, dict);
        }

    //console.log(lPairs);

    return findAns(lPairs, poly);
    }

function findAns(lPairs, poly)
    {
    var lCount = {};

    for (const [key, value] of Object.entries(lPairs))
        lCount[key[0]] = lCount[key[0]] == undefined ? value : (lCount[key[0]] + value);
            

    // Add last letter
    lCount[poly[poly.length - 1]] += 1;

    //console.log(lCount);
    
    var max = 0;
    var min = Number.MAX_SAFE_INTEGER;
    for (const [key, value] of Object.entries(lCount))
        {
        if (value > max)
            max = value;

        if (value < min)
            min = value;
        }

    return (max - min) + " - is wrong";
    }

function applyStep(lPairs, dict)
    {
    var newLPairs = {};
    for (const [key, value] of Object.entries(lPairs))
        {
        var pair1 = key[0] + dict[key];
        var pair2 = dict[key] + key[1];

        newLPairs[pair1] = newLPairs[pair1] == undefined ? value : (newLPairs[pair1] + value);
        newLPairs[pair2] = newLPairs[pair2] == undefined ? value : (newLPairs[pair2] + value);
        }

    return newLPairs;
    }

function createLetterPairs(poly)
    {
    var lPairs = {};
    for (var c = 1; c < poly.length; c++)
        {
        var pair = poly[c-1] + poly[c];
        lPairs[pair] = 1;
        }

    return lPairs;
    }

function createDict(input)
    {
    var dict = {};

    for (var i = 0; i < input.length; i++)
        {
        var line = input[i].split(" -> ");
        dict[line[0]] = line[1];
        }
    
    return dict;
    }
    
module.exports.solution = solution;
