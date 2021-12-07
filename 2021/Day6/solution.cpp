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
    int birthDay;

    Lanternfish(int birthDay)
        {
        this->birthDay = birthDay;
        }

    long CountFishCreated()
        {
        long fishMadeDirectly = (birthDay / 7) + 1;
        long fishMadeInTotal = fishMadeDirectly;

        // Assume fish one is made 7 days after birthday 
        for (int i = 1; i < fishMadeDirectly; i++)
            {
            Lanternfish* newFish = new Lanternfish(birthDay - 7*i);
            fishMadeInTotal += newFish->CountFishCreated();
            }

        return fishMadeInTotal;
        }
    };

class Lanternfish_Part1
    {
public:
    int counter;

    Lanternfish_Part1(int initialValue)
        {
        counter = initialValue;
        }

    void DecreaseCounter()
        {
        counter--;
        }

    Lanternfish_Part1 MakeNewFish()
        {
        Lanternfish_Part1* newFish = new Lanternfish_Part1(DAYS_UNTIL_FIRST_BABY);
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

vector<Lanternfish_Part1> ConvertToFishes(vector<int> ages)
    {
    vector<Lanternfish_Part1> fishes;
    for (int i = 0; i < ages.size(); i++)
        {
        fishes.push_back(*(new Lanternfish_Part1(ages[i])));
        }

    return fishes;
    }

vector<Lanternfish_Part1> GetAges(vector<Lanternfish_Part1> fishes, int desiredAge)
    {
    vector<Lanternfish_Part1> desiredFishes;
    for (int i = 0; i < fishes.size(); i++)
        {
        if (fishes[i].counter == desiredAge)
            desiredFishes.push_back(fishes[i]);
        }

    return desiredFishes;
    }

long SimulateLife(vector<Lanternfish_Part1> fishes, int days)
    {
    for (int i = 0; i < days; i++)
        {
        cout << "Day " << i << " -- Num fish: " << fishes.size() << endl;
        vector<Lanternfish_Part1> newFish;
        for (int f = 0; f < fishes.size(); f++)
            {
            if (fishes[f].counter == 0)
                newFish.push_back(fishes[f].MakeNewFish());
            else 
                fishes[f].DecreaseCounter();
            }

        for (int nfish = 0; nfish < newFish.size(); nfish++)
            {
            fishes.push_back(newFish[nfish]);
            }
        }

    return fishes.size();
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
    vector<Lanternfish_Part1> fishes = ConvertToFishes(ages);
    
    // Add implementation function here
    Lanternfish_Part1* myFish = new Lanternfish_Part1(6);
    vector<Lanternfish_Part1> singleFish;
    singleFish.push_back(*myFish);
    int result = SimulateLife(singleFish, 80);

    //Lanternfish* day1Fish = new Lanternfish(254);
    //long fishMade = day1Fish->CountFishCreated();

    //cout << "Fish with starting age of 1 made: " << fishMade << " fish" << endl;

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
