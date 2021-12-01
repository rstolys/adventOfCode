
import pkg from 'xhr2';
const { XMLHttpRequest} = pkg;

/**
 * Read a file from the local 
 * @example
 * @param filename the path to the file
 */
function readFile(filename, callback)
    {
    var systemFileName = "file:///" + filename;

    var rawFile = new XMLHttpRequest();
    rawFile.open('GET', systemFileName, false);
    rawFile.onreadystatechange = function ()
        {
            if(rawFile.readyState === XMLHttpRequest.DONE)
            {
                if(rawFile.status === 200 || rawFile.status == 0)
                {
                    var allText = rawFile.responseText;
                    console.log(allText);
                    callback(allText);
                }
            }
        }
    }

export { readFile }