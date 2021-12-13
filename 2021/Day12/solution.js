var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

var data = readTextFile("file:///Users/rstolys/Developer/adventOfCode/2021/Day12/data.txt");
//console.log(data);

var nodes = [];
 data.forEach(element => 
    {
    var splitElements = element.split("-");

    nodes.push({
        n1: splitElements[0],
        n2: splitElements[1]
        });

    nodes.push({
        n1: splitElements[1],
        n2: splitElements[0]
        });
    });
//console.log(nodes);

// merge data for node 1
var newNodes = [];
nodes.forEach((node1, index1) => 
    {
    if (newNodes.find(item => item.node == node1.n1) != undefined)
        return; 

    var newNode = {node: node1.n1, neighbours: [node1.n2]};

    nodes.forEach((node2, index2) => 
        {
        if (index1 == index2)
            return;
        else if (node2.n1 != node1.n1)
            return;

        newNode.neighbours.push(node2.n2);
        });
    
    newNodes.push(newNode);
    });

console.log(newNodes);

var startNode = newNodes.find(item => item.node == "start");

var start = {pos: startNode.node, smallCaves: [startNode.node], twice: ""};
var ans = 0;
var Q = [start];
while(Q.length >= 1)
    {
    var element = Q.shift();
    if (element.pos == "end")
        {
        ans += 1;
        continue;
        }
    
    var currentNode = newNodes.find(item => item.node == element.pos);
    currentNode.neighbours.forEach( node =>
        {
        if (element.smallCaves.find(item => item == node) == undefined)
            {
            var newSmallCavesList = [];
            element.smallCaves.forEach( cave => newSmallCavesList.push(cave));
            if (node.toLowerCase() == node)
                newSmallCavesList.push(node);

            Q.push({pos: node, smallCaves: newSmallCavesList, twice: element.twice});
            }
        else if (element.smallCaves.find(item => item == node) != undefined &&
            element.twice == "" && node != "start" && node != "end")
            {
            Q.push({pos: node, smallCaves: element.smallCaves, twice: node});
            }
        });
    }

console.log(ans);


function readTextFile(file)
    {
    var textArray;
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function()
        {
        if(rawFile.status === 200 || rawFile.status == 0)
            {
            var fileText = rawFile.responseText;
            textArray = fileText.toString().replace(/\r\r/g, '\n').split('\n');
            }
        }
    rawFile.send(null);

    return textArray;
    }