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
const string FWD = "forward";
const string DOWN = "down";
const string UP = "up";

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/



/**
 * @brief Reads the data file of integers
 * 
 * @return vector<int> 
 */
vector<string> readFile()
    {
    string line;
    vector<string> dataVector;
    ifstream dataFile("data.txt");

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

int findMovement(string move, string moveType)
    {
    int endIndex = 8; // Assume it is FWD

    if (moveType == DOWN)
        endIndex = 5;
    else if (moveType == UP)
        endIndex = 3;

    return stoi(move.erase(0, endIndex));
    }

int findPosition(vector<string> data)
    {
    int horizontalPos = 0;
    int verticalPos = 0;
    int aim = 0;

    for (int i = 0; i < data.size(); i++)
        {
        // Determine the type of movement
        string movement = data[i];

        // If FWD is found in the string
        if (movement.find(FWD) != string::npos)
            {
            int horizontalMovement = findMovement(movement, FWD);
            horizontalPos += horizontalMovement;
            verticalPos += aim * horizontalMovement;
            }
        else if (movement.find(DOWN) != string::npos)
            {
            aim += findMovement(movement, DOWN);
            }
        else if (movement.find(UP) != string::npos)
            {
            aim -= findMovement(movement, UP);
            }
        else 
            {
            cout << "No movement matched: " << movement << endl;
            }
        }

    cout << "RESULTS:" << endl;
    cout << "Horizontal: " << horizontalPos << endl;
    cout << "Veritical: " << verticalPos << endl;
    int result = horizontalPos * verticalPos;
    cout << "Solution: " << result << endl;

    return result;
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
    vector<string> data = readFile();

    int result = findPosition(data);

    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
