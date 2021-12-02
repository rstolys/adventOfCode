/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 1 Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include "../../Utils/file.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

const string FWD = "forward";
const string DOWN = "down";
const string UP = "up";

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

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

    vector<string> data = util->readFileOfStrings(FILE_NAME);

    int result = findPosition(data);

    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
