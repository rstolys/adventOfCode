/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 08 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

class Box
    {
    distances = {};

    connectedTo = [];

    constructor(cordinate)
        {
        this.id = cordinate;

        let [x, y, z] = cordinate.split(',').map(Number);
        this.x = x;
        this.y = y;
        this.z = z;
        }

    computeDistanceTo(otherBox)
        {
        let val1 = ((this.x - otherBox.x) ** 2) +
            ((this.y - otherBox.y) ** 2) +
            ((this.z - otherBox.z)** 2);

        this.distances[otherBox.id] = { box: otherBox, distance: Math.sqrt(val1) };
        }

    getNextClosestBoxDistance()
        {
        let minDistance = Infinity;
        let closestBoxId = null;

        for (let [boxId, info] of Object.entries(this.distances))
            {
            // If these boxes are already connected, skip
            if (this.connectedTo.includes(boxId))
                continue;

            if (info.distance < minDistance)
                {
                minDistance = info.distance;
                closestBoxId = boxId;
                }
            }

        return { boxId: this.id, closestTo: closestBoxId, distance: minDistance };
        }
    }

function solution(data)
    {
    // Create all the boxes
    let boxes = {};
    for (let i = 0; i < data.length; i++)
        boxes[data[i]] = new Box(data[i]);
    
    // Compute distances between all boxes
    let boxArray = Object.values(boxes);
    for (let i = 0; i < boxArray.length; i++)
        for (let j = 0; j < boxArray.length; j++)
            if (i !== j)
                boxArray[i].computeDistanceTo(boxArray[j]);

    // Connect the n closest boxes
    let n = 10;
    let availableClosestConnections = [];
    for (let i = 0; i < n; i++)
        {
        for (let j = 0; j < boxArray.length; j++)
            availableClosestConnections.push(boxArray[j].getNextClosestBoxDistance());

        // Sort the available connections by distance
        availableClosestConnections = availableClosestConnections.sort((a,b) => a.distance - b.distance);

        // Connect the closest boxes
        let closestConnection = availableClosestConnections.shift();
        boxes[closestConnection.boxId].connectedTo.push(closestConnection.closestTo);

        // Clear the available connections for the next iteration
        availableClosestConnections = [];
        }

    // Traverse the connections to find all of the chain lengths 
    let chainLengths = [];
    let visitedNodes = {};
    for (let i = 0; i < boxArray.length; i++)
        {
        if (visitedNodes[boxArray[i].id])
            continue;

        chainLengths.push(buildChain(visitedNodes, boxArray[i], boxes));
        }

    chainLengths = chainLengths.sort((a,b) => b - a);
    return chainLengths[0] * chainLengths[1] * chainLengths[2];
    }

function buildChain(visitedNodes, currentBox, allBoxes)
    {
    if (visitedNodes[currentBox.id])
        return 0; 

    visitedNodes[currentBox.id] = true;

    let numConnectedBoxes = 0;
    for (let i = 0; i < currentBox.connectedTo.length; i++)
        numConnectedBoxes += buildChain(visitedNodes, allBoxes[currentBox.connectedTo[i]], allBoxes);

    return numConnectedBoxes + 1;
    }
    
module.exports.solution = solution;
