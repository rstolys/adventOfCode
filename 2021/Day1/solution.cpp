/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 30 Nov 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/***DEFINES*******************************************************************/


/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/



/**
 * @brief Reads the data file of integers
 * 
 * @return vector<int> 
 */
vector<int> readFile()
    {
    string line;
    vector<int> intVector;
    ifstream dataFile("data.txt");

    if (dataFile.is_open())
        {
        while (getline(dataFile, line))
        {
            intVector.push_back(stoi(line));
        }

        dataFile.close();
        }
    else 
        cout << "Unable to open file"; 

    return intVector;
    }

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


///////////////////////////////////////////////////////////////////
/// MAIN FUNCTION
///
/// @param[in]  argc    number of command line arguements
/// @param[in]  argv    array of command line arguements
///
///////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
    {
    vector<int> data = readFile();

    cout << findNumberOfIncreases(data) << endl;
    return 0;
    }
