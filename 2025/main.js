// Set the current day
const currentDay = "Day12";

var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
var s = require("./" + currentDay + "/solution");

// Read Data
var data = readTextFile("file:///Users/rstolys/Developer/adventOfCode/2025/" + currentDay + "/data.txt");

// Complete Solution
var result = s.solution(data);

// Report Result
console.log(" ");
console.log("Answer Reported:")
console.log(result);

//Read Data Function
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