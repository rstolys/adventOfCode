/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 20 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

function solution(data)
    {
    let freshIndredientRanges = [];
    let indredientIds = [];
    let isListingIds = false;
    for (let i = 0; i < data.length; i++)
        {
        if (isListingIds)
            {
            indredientIds.push(Number(data[i]));
            }
        else 
            {
            if (data[i] == "")
                {
                isListingIds = true;
                continue;
                }

            freshIndredientRanges.push(data[i].split("-").map(Number));
            }
        }

    freshIndredientRanges = freshIndredientRanges.sort((a, b) => a[0] - b[0]);

    // Part 1
    // let freshIngredients = 0;
    // for (let i = 0; i < indredientIds.length; i++)
    //     {
    //     freshIngredients += isIngredientFresh(freshIndredientRanges, indredientIds[i]) ? 1 : 0;
    //     }

    // return freshIngredients;

    let totalFreshIngredients = 0;
    let lastFreshIngredient = 0;
    for (let i = 0; i < freshIndredientRanges.length; i++)
        {
        if (lastFreshIngredient >= freshIndredientRanges[i][1])
            continue;
        else if (lastFreshIngredient >= freshIndredientRanges[i][0])
            totalFreshIngredients += freshIndredientRanges[i][1] - lastFreshIngredient;
        else 
            totalFreshIngredients += freshIndredientRanges[i][1] - freshIndredientRanges[i][0] + 1;

        lastFreshIngredient = freshIndredientRanges[i][1];
        }

    return totalFreshIngredients;
    }

function isIngredientFresh(freshSet, id)
    {
    for (let i = 0; i < freshSet.length; i++)
        {
        if (id >= freshSet[i][0] && id <= freshSet[i][1])
            return true;

        if (id < freshSet[i])
            break;
        }

    return false;
    }


    
module.exports.solution = solution;
