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
const int CHAR_TO_INT = 48;

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class Octopus
    {
public:
    int row;
    int col;
    int value;
    bool flashed;
    bool neighboursNotified;

    Octopus* above;
    Octopus* aboveLeft;
    Octopus* aboveRight;
    Octopus* below;
    Octopus* belowLeft;
    Octopus* belowRight;
    Octopus* left;
    Octopus* right;

    Octopus(int r, int c, int v)
        {
        row = r;
        col = c;
        value = v;
        flashed = false;
        neighboursNotified = false;
        }

    void SetNeighbours(Octopus* a, Octopus* al, Octopus* ar, Octopus* b, Octopus* bl, Octopus* br, Octopus* l, Octopus* r)
        {
        above = a;
        aboveLeft = al;
        aboveRight = ar;
        below = b;
        belowLeft = bl;
        belowRight = br;
        left = l;
        right = r;
        }
    
    void IncreaseEnergy()
        {
        value++;
        }

    int FlashIfNeeded()
        {
        if (flashed)
            return 0;
        else if (value > 9)
            {
            flashed = true;
            return 1;
            }
        else 
            return 0;
        }
    
    void NotifyNeighbourOfFlash()
        {
        // Tell neighbours about flash
        if (flashed && !neighboursNotified)
            {
            if (above != nullptr)
                above->IncreaseEnergy();

            if (aboveRight != nullptr)
                aboveRight->IncreaseEnergy();

            if (aboveLeft != nullptr)
                aboveLeft->IncreaseEnergy();

            if (below != nullptr)
                below->IncreaseEnergy();

            if (belowLeft != nullptr)
                belowLeft->IncreaseEnergy();

            if (belowRight != nullptr)
                belowRight->IncreaseEnergy();

            if (left != nullptr)
                left->IncreaseEnergy();

            if (right != nullptr)
                right->IncreaseEnergy();

            neighboursNotified = true;
            }
        }

    void EndStep()
        {
        if (flashed)
            value = 0;

        flashed = false;
        neighboursNotified = false;
        }
    };

class Grid
    {
public:
    vector< vector<Octopus*> > grid;

    Grid(vector<string> data)
        {
        SetGrid(data); 
        PrintGrid();

        // Set Neighbours
        SetNeighbours();
        }

    int SimulateSteps(int steps)
        {
        int flashes = 0;
        for (int s = 0; s < steps; s++)
            {
            // Print Step
            cout << "Step: " << s << endl;
            
            // Increase Energy
            for (int r = 0; r < grid.size(); r++)
                {
                for (int c = 0; c < grid[r].size(); c++)
                    {
                    grid[r][c]->IncreaseEnergy();
                    }
                }

            int newFlashes = 0;
            int flashesThisStep = 0;
            do 
                {
                newFlashes = 0;
                // Flash
                for (int r = 0; r < grid.size(); r++)
                    {
                    for (int c = 0; c < grid[r].size(); c++)
                        {
                        newFlashes += grid[r][c]->FlashIfNeeded();
                        }
                    }

                // Notify Neightbours of flash
                for (int r = 0; r < grid.size(); r++)
                    {
                    for (int c = 0; c < grid[r].size(); c++)
                        {
                        grid[r][c]->NotifyNeighbourOfFlash();
                        }
                    }

                flashesThisStep += newFlashes;
                }
            while (newFlashes);

            flashes += flashesThisStep;
            cout << flashesThisStep << endl;
            if (flashesThisStep > 99)
                break;
            
            
            // End Step
            for (int r = 0; r < grid.size(); r++)
                {
                for (int c = 0; c < grid[r].size(); c++)
                    {
                    grid[r][c]->EndStep();
                    }
                }
            }

        return flashes;
        }

private:
    void SetGrid(vector<string> data)
        {
        for (int r = 0; r < data.size(); r++)
            {
            vector<Octopus*> newOctupuses;
            grid.push_back(newOctupuses);

            for (int c = 0; c < data[r].length(); c++)
                {
                int value = (int)data[r][c] - CHAR_TO_INT;
                Octopus* newOctupus = new Octopus(r, c, value);
                grid[r].push_back(newOctupus);
                }
            }
        }

    void SetNeighbours()
        {
        for (int r = 0; r < grid.size(); r++)
            {
            for (int c = 0; c < grid[r].size(); c++)
                {
                Octopus* above = (r == 0) ? nullptr : grid[r-1][c];
                Octopus* below = (r == grid.size() - 1) ? nullptr : grid[r+1][c];
                Octopus* left = (c == 0) ? nullptr : grid[r][c-1];
                Octopus* right = (c == grid[r].size() - 1) ? nullptr : grid[r][c+1];

                Octopus* aboveL = (r == 0 || c == 0) ? nullptr : grid[r-1][c-1];
                Octopus* aboveR = (r == 0 || c == grid.size() - 1) ? nullptr : grid[r-1][c+1];
                Octopus* belowL = (r == grid.size() - 1 || c == 0) ? nullptr : grid[r+1][c-1];
                Octopus* belowR = (r == grid.size() - 1 || c == grid.size() - 1) ? nullptr : grid[r+1][c+1];

                grid[r][c]->SetNeighbours(above, aboveL, aboveR, below, belowL, belowR, left, right);
                }
            }
        }

    void PrintGrid()
        {
        for (int r = 0; r < grid.size(); r++)
            {
            for (int c = 0; c < grid[r].size(); c++)
                {
                cout << grid[r][c]->value;
                }
            cout << endl;
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

    vector<string> data = util->readFile(FILE_NAME);

    Grid* grid = new Grid(data);

    // Add implementation function here
    int result = grid->SimulateSteps(500);

    // Report Result
    cout << endl << "Reported Result: " << result << endl;
    cout << endl << "Looking for: 1656" << endl;

    return 0;
    }
