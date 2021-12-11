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
const int CHAR_TO_INT = 48;

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
    vector<string> readFile(string fileName);

    /**
     * @brief Convert a string vector to an int vector
     * 
     * @param dataIn The data in
     * @return vector<int> Vector where each element is an int
     */
    vector<int> convertStringsToInts(vector<string> dataIn);

    /**
     * @brief Convert a string vector to an int vector
     * 
     * @param dataIn The data in
     * @return vector<int> Vector where each element is a long
     */
    vector<long> convertStringsToLongs(vector<string> dataIn);

    /**
     * @brief Read a file where each line is an int
     * 
     * @param fileName The name of the file to fetch the data from
     * @return vector<int> Vector where each element is line of data
     */
    vector<int> convertCsvToInt(string data);

    /**
     * @brief convery a string of characters to integers. Each a single digit
     * 
     * @param data The string of data
     * @return vector<int> Vector where each element is a number
     */
    vector<int> convertStringToInts(string data);

    /**
     * @brief Convert a vector of strings to a grid of ints
     * 
     * @param data The vector of strings
     * @return vector< vector<int> > the grid of ints
     */
    vector< vector<int> > convertStringVectorToIntVectors(vector<string> data);
    };


/***FUNCTION DEFINITIONS******************************************************/
vector<string> Utils::readFile(string fileNameIn)
    {
    string fileName = fileNameIn == "" ? "data.txt" : fileNameIn;

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

vector<int> Utils::convertStringsToInts(vector<string> dataIn)
    {
    vector<int> data;

    for (int i = 0; i < dataIn.size(); i++)
        {
        data.push_back(stoi(dataIn[i]));
        }

    return data;
    }

vector<long> Utils::convertStringsToLongs(vector<string> dataIn)
    {
    vector<long> data;

    for (int i = 0; i < dataIn.size(); i++)
        {
        data.push_back(stol(dataIn[i]));
        }

    return data;
    }

vector<int> Utils::convertCsvToInt(string dataline)
    {
    vector<int> data;

    while (dataline.length())
        {
        size_t delimiterPos = dataline.find(',');
        int delimiterLength = 1;

        string value = dataline.substr(0, delimiterPos);

        // remove comma
        dataline.erase(0, delimiterPos + delimiterLength);

        data.push_back(stoi(value));

        if (delimiterPos == string::npos)
            break;
        }
    
    return data;
    }

vector<int> Utils::convertStringToInts(string dataline)
    {
    vector<int> data;

    for (int i = 0; i < dataline.length(); i++)
        {
        data.push_back((int)dataline[i] - CHAR_TO_INT);
        }

    return data;
    }

vector< vector<int> > Utils::convertStringVectorToIntVectors(vector<string> dataIn)
    {
    vector< vector<int> > data; 

    for (int i = 0; i < dataIn.size(); i++)
        {
        data.push_back(convertStringToInts(dataIn[i]));
        }

    return data;
    }