/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 1 Dec 2021	Ryan Stolys
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
class Utils
    { 
public:
    /**
     * @brief Read a file where each line is a string
     * 
     * @param fileName The name of the file to fetch the data from
     * @return vector<string> Vector where each element is line of data
     */
    vector<string> readFileOfStrings(string fileName);

    /**
     * @brief Read a file where each line is an int
     * 
     * @param fileName The name of the file to fetch the data from
     * @return vector<int> Vector where each element is line of data
     */
    vector<int> readFileOfInts(string fileName);

    /**
     * @brief Read a file where each line is an int
     * 
     * @param fileName The name of the file to fetch the data from
     * @return vector<long> Vector where each element is line of data
     */
    vector<long> readFileOfLongs(string fileName);
    };


/***FUNCTION DEFINITIONS******************************************************/
vector<string> Utils::readFileOfStrings(string fileName)
    {
    string line;
        vector<string> dataVector;
        ifstream dataFile(fileName);

        if (dataFile.is_open())
            {
            while (getline(dataFile, line))
            {
                dataVector.push_back(line);
            }

            dataFile.close();
            }
        else 
            cout << "Unable to open file"; 

    return dataVector;
    }

vector<int> Utils::readFileOfInts(string fileName)
    {
    string line;
        vector<int> intVector;
        ifstream dataFile(fileName);

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

vector<long> Utils::readFileOfLongs(string fileName)
    {
    string line;
        vector<long> intVector;
        ifstream dataFile(fileName);

        if (dataFile.is_open())
            {
            while (getline(dataFile, line))
            {
                intVector.push_back(stol(line));
            }

            dataFile.close();
            }
        else 
            cout << "Unable to open file"; 

    return intVector;
    }