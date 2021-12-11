/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * ?? Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include "../../Utils/utils.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/
class Submarine
    {
public:
    int pos;

    Submarine(int initalPos)
        {
        pos = initalPos;
        }

    void Print()
        {
        cout << pos << endl;
        }

    int DetermineFuelNeeded(int moveTo)
        {
        int posToMove = moveTo - pos;

        if (posToMove < 0)
            posToMove = -1 * posToMove;

        int fuel = 0;

        for (int i = 1; i <= posToMove; i++)
            {
            fuel += i;
            }
    
        return fuel;
        }
    };

/**
 * Not General
 */
vector<Submarine> GetSubs(string inputs)
    {
    vector<Submarine> subs;

    while (inputs.size() > 4)
        {
        size_t delimiterPos = inputs.find(",");
        int delimiterLength = 1;

        string value = inputs.substr(0, delimiterPos);

        // remove comma
        inputs.erase(0, delimiterPos + delimiterLength);

        Submarine* newSub = new Submarine(stoi(value));
        subs.push_back(*newSub);
        }

    // Add last value
    Submarine* newSub = new Submarine(stoi(inputs));
    subs.push_back(*newSub);
    
    return subs;
    }

int FindOptimalPos(vector<Submarine> subs)
    {
    int lowestFuel = -1;
    int atPosition = -1;

    for (int i = 0; i <= 1000; i++)
        {
        int fuelNeeded = 0;
        for (int j = 0; j < subs.size(); j++)
            {
            fuelNeeded += subs[j].DetermineFuelNeeded(i);
            }

        if (lowestFuel == -1 || fuelNeeded < lowestFuel)
            {
            lowestFuel = fuelNeeded;
            atPosition = i;
            }
        }

    cout << "Ideal location is: " << atPosition << endl;
    return lowestFuel;
    }

/**
 * @brief MAIN FUNCTION
 * 
 * @param argc number of command line arguements
 * @param argv array of command line arguements
 * @return int 
 */
int main (int argc, char **argv)
    {
    Utils* util = new Utils();

    vector<string> data = util->readFile(FILE_NAME);
    vector<Submarine> subs = GetSubs(data[0]);

    // Add implementation function here
    int result = FindOptimalPos(subs);

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
