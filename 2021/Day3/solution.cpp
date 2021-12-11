/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * ?? Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include "../../Utils/utils.cpp"
#include "../../Utils/binary.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";


/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

int findRates(vector<uint16_t> data)
    {
    Binary* binary = new Binary();
    int gamma = 0; // most common bit in each position

    for (int bit = 0; bit < 12; bit++)
        {
        gamma |= binary->determineMostCommonBitInGridColumn(data, bit) << bit;
        }

    int epsilon = binary->invertBits(gamma);
    int result = (gamma * epsilon);
    cout << "Gamma: " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Result: " << (gamma * epsilon) << endl;

    return result;
    }

int findO2Rating(vector<uint16_t> data)
    {
    Binary* binary = new Binary();
    uint16_t o2Rating = 0x0000;
    for (int bitPos = 11; bitPos >= 0; bitPos--)
        {
        int bit = binary->determineMostCommonBitInGridColumn(data, bitPos);

        //cout << "Most common bit: " << bit << endl;

        vector<uint16_t> filteredData;
        for (int i = 0; i < data.size(); i++)
            {
            if (((data[i] >> bitPos) & 0x1) == (bit & 0x1))
                filteredData.push_back(data[i]);
            }

        if (filteredData.size() == 1)
            {
            o2Rating = filteredData[0];
            cout << "Found O2 rating on bit: " << 11 - bitPos << endl;
            break;
            }

        data.clear();
        data = filteredData;
        }
    
    cout << "o2Rating: " << o2Rating << endl;
    return o2Rating;
    }

int findCO2Rating(vector<uint16_t> data)
    {
    Binary* binary = new Binary();
    uint16_t co2Rating = 0x0000;
    for (int bitPos = 11; bitPos >= 0; bitPos--)
        {
        // We actually want the least common bit
        int bit = !binary->determineMostCommonBitInGridColumn(data, bitPos);

        //cout << "Least common bit: " << bit << endl;

        vector<uint16_t> filteredData;
        for (int i = 0; i < data.size(); i++)
            {
            /*
            cout << data[i] << endl;
            cout << bitPos << endl;
            cout << (((data[i] >> bitPos) & 0x1)) << endl;
            cout << (bit & 0x1) << endl;
            cout << (((data[i] >> bitPos) & 0x1) == (bit & 0x1)) << endl;
            cout << "--END--" << endl;
            */
            if (((data[i] >> bitPos) & 0x1) == (bit & 0x1))
                filteredData.push_back(data[i]);
            }

        if (filteredData.size() == 1)
            {
            co2Rating = filteredData[0];
            cout << "Found CO2 rating after bit: " << 11 - bitPos << endl;
            break;
            }

        data.clear();
        data = filteredData;
        }
    
    cout << "co2Rating: " << co2Rating << endl;
    return co2Rating;
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
    Binary* binary = new Binary();

    vector<string> dataStrings = util->readFile(FILE_NAME);
    vector<uint16_t> data = binary->convertToBinaryValues(dataStrings);
    
    //int result = findRates(data);
    int oxygenRating = findO2Rating(data);
    int CO2rating = findCO2Rating(data);

    int result = oxygenRating * CO2rating;

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }