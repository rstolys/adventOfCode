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
#include "../../Utils/file.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/
const int CHAR_TO_INT = 48;
const int NONE = -1;
const int BELOW = 1;
const int ABOVE = 2;
const int LEFT = 3;
const int RIGHT = 4;

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class Point
    {
public:
    int row;
    int col;
    int value;
    bool lowPoint;
    bool checked;

    Point* above;
    Point* below;
    Point* left;
    Point* right;

    Point(int r, int c, int value)
        {
        row = r;
        col = c;
        this->value = value;
        
        checked = false;
        }

    void SetPoints(Point* above, Point* below, Point* left, Point* right)
        {
        this->above = above;
        this->below = below;
        this->left = left;
        this->right = right;

        SetLowPoint();
        }

    int FindBasinSize()
        {
        int basinSize = 1; 
        checked = true;

        //cout << "Finding Basin Size for " << row << " " << col << endl;

        if (above != nullptr && !above->checked && above->value < 9)
            basinSize += above->FindBasinSize();

        if (below != nullptr && !below->checked && below->value < 9)
            basinSize += below->FindBasinSize();

        if (left != nullptr && !left->checked && left->value < 9)
            basinSize += left->FindBasinSize();

        if (right != nullptr && !right->checked && right->value < 9)
            basinSize += right->FindBasinSize();

        return basinSize;
        }

private:
    void SetLowPoint()
        {
        bool isLowPoint = true;

        if (above != nullptr && above->value < value)
            isLowPoint = false;
        else if (below != nullptr && below->value < value)
            isLowPoint = false;
        else if (left != nullptr && left->value < value)
            isLowPoint = false;
        else if (right != nullptr && right->value < value)
            isLowPoint = false;

        lowPoint = isLowPoint;
        }
    };


class Tube
    {
public:
    vector<string> tubeDepths;
    vector< vector<Point*> > depths;

    Tube(vector<string> tubeDepths)
        {
        this->tubeDepths = tubeDepths;
    
        SetDepths();
        SetPointNeighbours();
        //PrintDepths();
        }

    int FindRiskLevel()
        {
        int riskSum = 0;

        for (int r = 0; r < depths.size(); r++)
            {
            for (int c = 0; c < depths[r].size(); c++)
                {
                if (depths[r][c]->lowPoint)
                    {
                    riskSum += depths[r][c]->value + 1;
                    }
                }
            }

        return riskSum;
        }

    int FindBiggestBasins()
        {
        int result = 0; 
        vector<int> basinSizes;

        for (int r = 0; r < depths.size(); r++)
            {
            for (int c = 0; c < depths[r].size(); c++)
                {
                if (depths[r][c]->lowPoint)
                    basinSizes.push_back(depths[r][c]->FindBasinSize());
                }
            }

        int biggestBasin = 0; 
        int secondBasin = 0; 
        int thirdBasin = 0;
        for (int r = 0; r < basinSizes.size(); r++)
            {
            if (basinSizes[r] >= biggestBasin)
                {
                thirdBasin = secondBasin;
                secondBasin = biggestBasin;
                biggestBasin = basinSizes[r];
                }
            else if (basinSizes[r] >= secondBasin)
                {
                thirdBasin = secondBasin;
                secondBasin = basinSizes[r];
                }
            else if (basinSizes[r] > thirdBasin)
                {
                thirdBasin = basinSizes[r];
                }

            }
        
        result = biggestBasin * secondBasin * thirdBasin;

        return result;
        }

private: 
    void SetDepths()
        {
        for (int r = 0; r < tubeDepths.size(); r++)
            {
            vector<Point*> newDepths;
            depths.push_back(newDepths);
            for (int c = 0; c < tubeDepths[r].length(); c++)
                {
                int value = (int)tubeDepths[r][c] - CHAR_TO_INT;
                Point* newPoint = new Point(r, c, value);
                depths[r].push_back(newPoint);
                }
            }
        }
    
    void SetPointNeighbours()
        {
        for (int r = 0; r < depths.size(); r++)
            {
            for (int c = 0; c < depths[r].size(); c++)
                {
                Point* above = (r == 0) ? nullptr : depths[r-1][c];
                Point* below = (r == depths.size() - 1) ? nullptr : depths[r+1][c];
                Point* left = (c == 0) ? nullptr : depths[r][c-1];
                Point* right = (c == depths[r].size() - 1) ? nullptr : depths[r][c+1];

                // SetDepths(Point* above, Point* below, Point* left, Point* right)
                depths[r][c]->SetPoints(above, below, left, right);
                }
            }
        }
    };

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

    Tube* tubes = new Tube(data);

    // Add implementation function here
    int result = tubes->FindBiggestBasins();
    //tubes->FindBasins();
    //tubes->PrintBasins();

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
