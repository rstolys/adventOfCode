/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 1 Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>


using namespace std;

/***DEFINES*******************************************************************/

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/
class Binary
    { 
public:
    /**
     * @brief Convert a string to a binary value
     * 
     * @param data A string of 0s and 1s
     * @return uint16_t A 16 bit binary value
     */
    uint16_t convertStringToBinary(string data);

    /**
     * @brief Convert array of strings to binary values
     * 
     * @param data An array of strings made up of 0s and 1s
     * @return vector<uint16_t> A vector of 16 bit values
     */
    vector<uint16_t> convertToBinaryValues(vector<string> data);

    /**
     * @brief Determines the most common bit in a grid column
     * 
     * @param data The gird of binary numbers
     * @param bitPos The bit position to consider
     * @return int A 1 or 0 depending on the most common bit
     */
    int determineMostCommonBitInGridColumn(vector<uint16_t> data, long bitPos);

    /**
     * @brief Invert the bits
     * 
     * @param input A binary Number
     * @return uint16_t An inverted binary number
     */
    uint16_t invertBits(uint16_t input);
    };


/***FUNCTION DEFINITIONS******************************************************/
uint16_t Binary::convertStringToBinary(string data)
    {
    uint16_t value = 0x0000;

    for (int b = 11, pos = 0; b >= 0; b--, pos++)
        {
        if (data[b] == '1')
            value |= 0x1 << pos; 
        }

    return value;
    }

vector<uint16_t> Binary::convertToBinaryValues(vector<string> data)
    {
    vector<uint16_t> convertedData;

    for (int i = 0; i < data.size(); i++)
        {
        string value = data[i];
        uint16_t binaryValue = convertStringToBinary(value);
        convertedData.push_back(binaryValue);
        }

    return convertedData;
    }

int Binary::determineMostCommonBitInGridColumn(vector<uint16_t> data, long bitPos)
    {
    int numOnes = 0;
    int numZeros = 0;

    for (int i = 0; i < data.size(); i++)
        {
        int bitValue = (data[i] >> bitPos) & 0x1;

        if (bitValue)
            numOnes++;
        else
            numZeros++;
        }

    return numOnes >= numZeros;
    }

uint16_t Binary::invertBits(uint16_t input)
    {
    for (int i = 0; i < 12; i++)
       input ^= (1 << i);

    return input;
    }