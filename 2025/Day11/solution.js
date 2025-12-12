/*-----------------------------------------------------------------------------
 * solution.js
 *
 * 11 Dec 2025	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/
class Device 
    {
    constructor(line)
        {
        let parts = line.split(':');
        this.Name = parts[0].trim();
        
        let outputs = parts[1].split(' ');
        this.Outputs = outputs.filter(o => o.trim() != "").map(o => o.trim());
        }
    }

const FFT = 'fft';
const DAC = 'dac';
const OUTPUT = 'out';

var devices = {};
function solution(data)
    {
    for (let line of data)
        {
        let device = new Device(line);
        devices[device.Name] = device;
        }

    //return findPathsPart1("you");
    return findPathsPart2("svr", false, false);
    }

function findPathsPart1(currentDevice)
    {
    if (currentDevice == OUTPUT)
        {
        return 1;
        } 
    else 
        {
        let otherPaths = 0;
        for (let connectedDevice of devices[currentDevice].Outputs)
            otherPaths += findPathsPart1(connectedDevice);

        return otherPaths;
        }
    }

var funcCache = {};
function findPathsPart2(currentDevice, seenFft, seenDac)
    {
    if (funcCache[buildKey(currentDevice, seenFft, seenDac)] != null)
        return funcCache[buildKey(currentDevice, seenFft, seenDac)];

    if (currentDevice == OUTPUT)
        {
        let result = (seenFft && seenDac) ? 1 : 0;
        funcCache[buildKey(currentDevice, seenFft, seenDac)] = result;
        } 
    else 
        {
        let otherPaths = 0;
        for (let connectedDevice of devices[currentDevice].Outputs)
            {
            let newSeenFft = seenFft || (connectedDevice == FFT);
            let newSeenDac = seenDac || (connectedDevice == DAC);
            otherPaths += findPathsPart2(connectedDevice, newSeenFft, newSeenDac);
            }

        funcCache[buildKey(currentDevice, seenFft, seenDac)] = otherPaths;
        }

    return funcCache[buildKey(currentDevice, seenFft, seenDac)];
    }

function buildKey(currentDevice, seenFft, seenDac)
    {
    return currentDevice + '|' + (seenFft ? '1' : '0') + '|' + (seenDac ? '1' : '0');   
    }
    
module.exports.solution = solution;
