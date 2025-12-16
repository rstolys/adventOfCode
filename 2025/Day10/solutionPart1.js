/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 15 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/

class PriorityQueue
    {
    constructor() 
        {
        this.elements = [];
        }

    // Enqueue an item with a priority (f_cost)
    Enqueue(item, priority) 
        {
        this.elements.push({ item, priority });
        // Sort the array every time an element is added to keep the highest priority (lowest value) at the front
        this.elements.sort((a, b) => a.priority - b.priority); 
        }

    // Dequeue the item with the highest priority (lowest f_cost)
    Dequeue() 
        {
        return this.elements.shift().item;
        }

    Contains(item)
        {
        return this.elements.some(element => element.item.GetKey() === item.GetKey());
        }

    isEmpty() 
        {
        return this.elements.length === 0;
        }
    }

class Node 
    {
    constructor(point, weight) 
        {
        this.point = point;
        this.weight = weight;
        }

    GetKey()
        {
        return this.point.join(",");
        }
    }

class Graph
    {
    constructor(nodes, paths)
        {
        //this.Nodes = nodes;
        this.Paths = paths;
        }
    }

function solution(data)
    {
    let totalButtonClicks = 0;
    for (let i = 0; i < data.length; i++)
        {
        let line = data[i];
        let parts = line.split(" ");
        let finalState = ParseFinalState(parts.shift());

        parts.pop(); // joltageReq -- We don't use this in part 1
        let buttonPresses = ParseButtonPress(finalState.length, parts);

        let result = Solve(new Node(Array(finalState.length).fill(0), 0), new Node(finalState, 0), buttonPresses);

        console.log(`${i}. Button Clicks: ${result.value}`);
        console.log(`${i}. Nodes: ${result.nodes.map(node => node.GetKey()).join(" -> ")}`);
        console.log(`${i}. Path: ${result.path.map(path => ConvertButtonPress(path)).join(" -> ")}`);
        
        totalButtonClicks += result.value;
        }

    return totalButtonClicks;    
    }

function Solve(startNode, targetNode, paths)
    {
    let openQueue = new PriorityQueue();
    openQueue.Enqueue(startNode, ComputeHeuristic(startNode, targetNode));

    let gScore = {};
    gScore[startNode.GetKey()] = 0;

    let cameFrom = {}; // Stores the path

    while (!openQueue.isEmpty())
        {
        let current = openQueue.Dequeue();

        // Check if we reached the target
        if (current.GetKey() === targetNode.GetKey())
            {
            let nodes = reconstructNodesOnPath(cameFrom, startNode, current);
            let path = reconstructPath(cameFrom, startNode, current);
            return { value: nodes.length - 1 , nodes: nodes, path: path };
            }

        // Explore the neighbors
        for (let path of paths)
            {
            let neighborPoint = current.point.map((val, idx) => val ^ path[idx]); // Toggle bits based on the path
            let pathCost = 1; // Each button press has a cost of 1
            let neighborNode = new Node(neighborPoint, pathCost);

            let tentativeGScore = gScore[current.GetKey()] + pathCost;

            if (tentativeGScore < (gScore[neighborNode.GetKey()] || Infinity))
                {
                cameFrom[neighborNode.GetKey()] = current;
                gScore[neighborNode.GetKey()] = tentativeGScore;

                if (!openQueue.Contains(neighborNode))
                    openQueue.Enqueue(neighborNode, tentativeGScore + ComputeHeuristic(neighborNode, targetNode));
                }

            }
        }

        return { value: 0, path: [] };
    }

function reconstructNodesOnPath(cameFrom, startingNode, current) 
    {
    let totalPath = [current];
    while (cameFrom[current.GetKey()].GetKey() != startingNode.GetKey()) 
        {
        current = cameFrom[current.GetKey()];
        totalPath.unshift(current);
        }

    totalPath.unshift(startingNode);
    return totalPath;
    }

function reconstructPath(cameFrom, startingNode, current) 
    {
    let pathElements = [];
    while (cameFrom[current.GetKey()].GetKey() != startingNode.GetKey()) 
        {
        let prev = current;
        current = cameFrom[current.GetKey()];

        // Determine the path taken to reach this node
        let path = prev.point.map((val, idx) => val ^ current.point[idx]);
        pathElements.unshift(path);
        }

    let path = startingNode.point.map((val, idx) => val ^ current.point[idx]);
    pathElements.unshift(path);

    return pathElements;
    }

// Compute the heuristic cost going from node A to node B
function ComputeHeuristic(A, B)
    {
    let weightOfPath = ComputeWeight(A.point, B.point);
    return weightOfPath + A.gScore;
    }

function ComputeWeight(node, target)
    {
    let weight = 0;
    for (let i = 0; i < node.length; i++)
        weight += Math.abs(node[i] - target[i]);

    return weight;
    }

// Convert the button pressed into path traversals
function ParseButtonPress(numButtons, buttonPresses)
    {
    let paths = [];
    for (let press of buttonPresses)
        {
        let trimmed = press.slice(1, -1);
        let buttonsPressed = trimmed.split(",").map(Number);
        let path = Array(numButtons).fill(0);
        for (let button of buttonsPressed)
            path[button] = 1;

        paths.push(path);
        }

    return paths;
    }

// Convert the array representation of button press into a string
function ConvertButtonPress(path)
    {
    let button = "(";
    for (let i = 0; i < path.length; i++)
        {
        if (path[i] == 1)
            button += i + ",";
        }

    button = button.slice(0, -1) + ")";
    return button;
    }

// Convert the final state into a data point on a graph
function ParseFinalState(input)
    {
    // Remove the first and last characters
    let trimmed = input.slice(1, -1);
    
    // Convert to data point
    return trimmed.split("").map(val => val == "#" ? 1 : 0);
    }
    
module.exports.solution = solution;
