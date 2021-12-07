/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 05 Dec 2021	Ryan Stolys
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
const int DAYS_UNTIL_BABY = 6;
const int DAYS_UNTIL_FIRST_BABY = 8;

const int CHAR_TO_INT = 48;

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/
class Lanternfish
    {
public:
    int counter;

    Lanternfish(int initialValue)
        {
        counter = initialValue;
        }

    void DecreaseCounter()
        {
        counter--;
        }

    Lanternfish MakeNewFish()
        {
        Lanternfish* newFish = new Lanternfish(DAYS_UNTIL_FIRST_BABY);
        counter = DAYS_UNTIL_BABY;

        return *(newFish);
        }

    };

vector<int> GetFishAges(string inputs)
    {
    vector<int> ages;

    for (int i = 0; i < inputs.size(); i += 2)
        {
        ages.push_back((int)inputs[i] - CHAR_TO_INT);
        }

    return ages;
    }

vector<Lanternfish> ConvertToFishes(vector<int> ages)
    {
    vector<Lanternfish> fishes;
    for (int i = 0; i < ages.size(); i++)
        {
        fishes.push_back(*(new Lanternfish(ages[i])));
        }

    return fishes;
    }

int GetNumAtCounter(vector<Lanternfish> fishes, int currentCounter)
    {
    int numFish = 0;
    for (int i = 0; i < fishes.size(); i++)
        {
        if (fishes[i].counter == currentCounter)
            numFish++;
        }

    return numFish;
    }

long SimulateLife(vector<long> fishPerDay, int days)
    {
    for (int i = 0; i < days; i++)
        {
        long babyMakingFish = fishPerDay[0];

        fishPerDay[0] = fishPerDay[1];
        fishPerDay[1] = fishPerDay[2];
        fishPerDay[2] = fishPerDay[3];
        fishPerDay[3] = fishPerDay[4];
        fishPerDay[4] = fishPerDay[5];
        fishPerDay[5] = fishPerDay[6];
        fishPerDay[6] = fishPerDay[7] + babyMakingFish;
        fishPerDay[7] = fishPerDay[8];
        fishPerDay[8] = babyMakingFish;
        }

    long totalFish = 0;
    for (int i = 0; i < 9; i++)
        {
        totalFish += fishPerDay[i];
        }

    return totalFish;
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

    vector<int> ages = GetFishAges(data[0]);

    // Convert to array of lanternfish
    vector<Lanternfish> fishes = ConvertToFishes(ages);

    cout << "Num Fish " << fishes.size() << endl; 

    vector<long> fishPerDay;
    fishPerDay.push_back(GetNumAtCounter(fishes, 0)); // Should be 0
    fishPerDay.push_back(GetNumAtCounter(fishes, 1));
    fishPerDay.push_back(GetNumAtCounter(fishes, 2));
    fishPerDay.push_back(GetNumAtCounter(fishes, 3));
    fishPerDay.push_back(GetNumAtCounter(fishes, 4));
    fishPerDay.push_back(GetNumAtCounter(fishes, 5));
    fishPerDay.push_back(GetNumAtCounter(fishes, 6)); 
    fishPerDay.push_back(GetNumAtCounter(fishes, 7)); // Shuold be 0
    fishPerDay.push_back(GetNumAtCounter(fishes, 8)); // Should be 0

    long result = SimulateLife(fishPerDay, 256);
    
    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
