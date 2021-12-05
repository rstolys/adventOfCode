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
int grid_gv[1000][1000];

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class Point 
    {
public: 
    int x;
    int y;

    Point() {}

    Point(int x, int y)
        {
        this->x = x;
        this->y = y;
        }
    };

class Line
    {
public: 
    Point start;
    Point end;
    vector<Point> pointsOnLine;

    Line(string input)
        {
        size_t delimiterPos = input.find(" -> ");
        int delimiterLength = 4;

        string point1 = input.substr(0, delimiterPos);
        
        // remove delimiter
        input.erase(0, delimiterPos + 4);

        string point2 = input;

        convertToCoordinates(point1, 1);
        convertToCoordinates(point2, 2);

        fillPointsOnLine();
        }

    void fillGrid()
        {
        for (int i = 0; i < pointsOnLine.size(); i++)
            grid_gv[pointsOnLine[i].x][pointsOnLine[i].y]++;
        }

private:
    void fillPointsOnLine()
        {
        int lastX = start.x;
        int lastY = start.y;

        if (start.x == end.x)
            {
            int nextDirection = start.y < end.y ? 1 : -1;
            bool lineNotDone = true;
            pointsOnLine.push_back(start);

            while (lineNotDone)
                {
                lastY += nextDirection;
                pointsOnLine.push_back(*(new Point(lastX, lastY)));

                if (lastY == end.y)
                    lineNotDone = false;
                }
            }
        else if (start.y == end.y)
            {
            int nextDirection = start.x < end.x ? 1 : -1;
            bool lineNotDone = true;
            pointsOnLine.push_back(start);

            while (lineNotDone)
                {
                lastX += nextDirection;
                pointsOnLine.push_back(*(new Point(lastX, lastY)));

                if (lastX == end.x)
                    lineNotDone = false;
                }
            }
        else 
            {
            int nextXDirection = start.x < end.x ? 1 : -1;
            int nextYDirection = start.y < end.y ? 1 : -1;
            bool lineNotDone = true;
            pointsOnLine.push_back(start);

            while (lineNotDone)
                {
                lastX += nextXDirection;
                lastY += nextYDirection;
                pointsOnLine.push_back(*(new Point(lastX, lastY)));

                if (lastX == end.x && lastY == end.y)
                    lineNotDone = false;
                }
            }
        }
    
    void convertToCoordinates(string coordinates, int forPoint)
        {
        size_t commaPos = coordinates.find(",");

        string x = coordinates.substr(0, commaPos);
        coordinates.erase(0, commaPos + 1);
        string y = coordinates;

        if (forPoint == 1)
            this->start = *(new Point(stoi(x), stoi(y)));
        else 
            this->end = *(new Point(stoi(x), stoi(y)));
        }
    };

void fillGlobalGrid(vector<Line> lines)
    {
    for (int i = 0; i < lines.size(); i++)
        lines[i].fillGrid();
    }

int countMultipleLines()
    {
    int numMultiple = 0;

    for (int i = 0; i < 1000; i++)
        {
        for (int j = 0; j < 1000; j++)
            {
            if (grid_gv[i][j] > 1)
                numMultiple++;
            }
        }

    return numMultiple;
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

    // Each string is a pair of points
    vector<string> data = util->readFileOfStrings(FILE_NAME);

    vector<Line> lines;
    for (int i = 0; i < data.size(); i++)
        lines.push_back(*(new Line(data[i])));

    fillGlobalGrid(lines);

    // Add implementation function here
    int result = countMultipleLines();

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
