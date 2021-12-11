/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 30 Nov 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include "../../Utils/utils.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

int findSum(vector<int> data, int index)
    {
    if (index > data.size() - 3)
        return -1;
    else 
        return data.at(index) + data.at(index + 1) + data.at(index +2);
    }

int findNumberOfIncreases(vector<int> data)
    {
    int numberIncreases = 0;
    int lastIndex = 0;
    int currentIndex = 1;

    while (true)
        {
        int current = findSum(data, currentIndex);
        int last = findSum(data, lastIndex);

        // End Condition
        if (current == -1)
            break;

        if (current > last)
            numberIncreases++;

        lastIndex = currentIndex;
        currentIndex++;
        }

    return numberIncreases;
    }

/**
 * @brief MAIN FUNCTION
 * 
 * @param argc number of command line arguements
 * @param argv array of command line arguements
 * @return int 
 */
int main( int argc, char **argv )
    {
    Utils* util = new Utils();

    vector<string> dataStrings = util->readFile(FILE_NAME);
    vector<int> data = util->convertStringsToInts(dataStrings);

    cout << findNumberOfIncreases(data) << endl;

    return 0;
    }
