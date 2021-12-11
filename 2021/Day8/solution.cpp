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


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class CodedNumber 
    {
public: 
    string value;

    CodedNumber(string input)
        {
        value = input;
        }

    bool IsSimpleNumber()
        {
        bool knownValue = false;

        if (value.length() == 2) // Number 1
            knownValue = true;
        else if (value.length() == 4) // Number 4
            knownValue = true;
        else if (value.length() == 3) // Number 7
            knownValue = true;
        else if (value.length() == 7) // Number 8
            knownValue = true;

        return knownValue;
        }
    };

class NumberGrid
    {
    ///  pos1
    /// p    p
    /// o    o
    /// s    s 
    /// 2    3
    ///  pos4
    /// p    p
    /// o    o
    /// s    s 
    /// 5    6
    ///  pos7
public:
    char pos1;
    char pos2;
    char pos3;
    char pos4;
    char pos5;
    char pos6;
    char pos7;
    vector<string> numbers;

    // The numbers must be in order
    NumberGrid(vector<string> numbers)
        {
        this->numbers = numbers;
        // Set the pos characters
        setPos1(numbers);
        setPos2(numbers);
        setPos3(numbers);
        setPos4(numbers);
        setPos5(numbers);
        setPos6(numbers);
        setPos7(numbers);
        }

    int DetermineNumberAttempt2(string value)
        {
        int number = 0;

        for (int i = 0; i < numbers.size(); i++)
            {
            if (numbers[i].length() != value.length())
                continue;

            bool allMatches = true;
            for (int c = 0; c < value.length(); c++)
                {
                if (!ContainsChar(numbers[i], value[c]))
                    allMatches = false;
                }

            if (allMatches)
                {
                number = i;
                break;
                }
            }

        return number;
        }

    int DetermineNumber(string value)
        {
        int number = 0;

        if (value.length() == 2) // Number 1
            number = 1;
        else if (value.length() == 4) // Number 4
            number = 4;
        else if (value.length() == 3) // Number 7
            number = 7;
        else if (value.length() == 7) // Number 8
            number = 8;
        else 
            {
            if (value.length() == 5) // Number is 2, 3, 5
                {
                bool isNum5 = false;
                bool isNum2 = false;
                for (int c = 0; c < 5; c++)
                    {
                    if (pos2 == value[c])
                        isNum5 = true;

                    if (pos5 == value[c])
                        isNum2 = true;
                    }

                if (isNum5)
                    number = 5;
                else if (isNum2)
                    number = 2;
                else 
                    number = 3;
                }
            else if (value.length() == 6) // Number is 0, 6, 9
                {
                bool containsPos4 = false;
                bool containsPos3 = false;
                for (int c = 0; c < 5; c++)
                    {
                    if (pos4 == value[c])
                        containsPos4 = true;

                    if (pos3 == value[c])
                        containsPos3 = true;
                    }

                if (containsPos4)
                    {
                    if (containsPos3)
                        number = 9;
                    else 
                        number = 6;
                    }
                else 
                    {
                    number = 0;
                    }
                }
            }

        return number;
        }

private: 
    void setPos1(vector<string> numbers)
        {
        // character will exist in 0, 2, 3, 5, 6, 7, 8, 9
        string num7 = numbers[7];
        char pos1Char;
        for (int c = 0; c < num7.length(); c++)
            {
            pos1Char = num7[c];

            if (ContainsChar(numbers[0], pos1Char) && !ContainsChar(numbers[1], pos1Char) &&
                ContainsChar(numbers[2], pos1Char) && ContainsChar(numbers[3], pos1Char) && 
                !ContainsChar(numbers[4], pos1Char) && ContainsChar(numbers[5], pos1Char) &&
                ContainsChar(numbers[6], pos1Char) && ContainsChar(numbers[8], pos1Char) &&
                ContainsChar(numbers[9], pos1Char))
                break;
            }

        pos1 = pos1Char;
        }

    void setPos2(vector<string> numbers)
        {
        // character will exist in 0, 4, 5, 6, 8, 9
        string num4 = numbers[4];
        char pos2Char;
        for (int c = 0; c < num4.length(); c++)
            {
            pos2Char = num4[c];

            if (ContainsChar(numbers[0], pos2Char) && !ContainsChar(numbers[1], pos2Char) &&
                !ContainsChar(numbers[2], pos2Char) && !ContainsChar(numbers[3], pos2Char) && 
                ContainsChar(numbers[5], pos2Char) &&
                ContainsChar(numbers[6], pos2Char) && !ContainsChar(numbers[7], pos2Char) &&
                ContainsChar(numbers[8], pos2Char) && ContainsChar(numbers[9], pos2Char))
                break;
            }

        pos2 = pos2Char;
        }

    void setPos3(vector<string> numbers)
        {
        // character will exist in 0, 1, 2, 3, 4, 7, 8, 9
        string num1 = numbers[1];
        char pos3Char;
        for (int c = 0; c < num1.length(); c++)
            {
            pos3Char = num1[c];

            if (ContainsChar(numbers[0], pos3Char) &&
                ContainsChar(numbers[2], pos3Char) && ContainsChar(numbers[3], pos3Char) && 
                ContainsChar(numbers[4], pos3Char) && !ContainsChar(numbers[5], pos3Char) &&
                !ContainsChar(numbers[6], pos3Char) && ContainsChar(numbers[7], pos3Char) &&
                ContainsChar(numbers[8], pos3Char) && ContainsChar(numbers[9], pos3Char))
                break;
            }

        pos3 = pos3Char;
        }

    void setPos4(vector<string> numbers)
        {
        // character will exist in 2, 3, 4, 5, 6, 8, 9
        string num4 = numbers[4];
        char pos4Char;
        for (int c = 0; c < num4.length(); c++)
            {
            pos4Char = num4[c];

            if (!ContainsChar(numbers[0], pos4Char) && !ContainsChar(numbers[1], pos4Char) &&
                ContainsChar(numbers[2], pos4Char) && ContainsChar(numbers[3], pos4Char) && 
                ContainsChar(numbers[5], pos4Char) &&
                ContainsChar(numbers[6], pos4Char) && !ContainsChar(numbers[7], pos4Char) &&
                ContainsChar(numbers[8], pos4Char) && ContainsChar(numbers[9], pos4Char))
                break;
            }

        pos4 = pos4Char;
        }
    
    void setPos5(vector<string> numbers)
        {
        // character will exist in 0, 2, 6, 8
        string num2 = numbers[2];
        char pos5Char;
        for (int c = 0; c < num2.length(); c++)
            {
            pos5Char = num2[c];

            if (ContainsChar(numbers[0], pos5Char) && !ContainsChar(numbers[1], pos5Char) &&
                !ContainsChar(numbers[3], pos5Char) && 
                !ContainsChar(numbers[4], pos5Char) && !ContainsChar(numbers[5], pos5Char) &&
                ContainsChar(numbers[6], pos5Char) && !ContainsChar(numbers[7], pos5Char) &&
                ContainsChar(numbers[8], pos5Char) && !ContainsChar(numbers[9], pos5Char))
                break;
            }

        pos5 = pos5Char;
        }
        
    void setPos6(vector<string> numbers)
        {
        // character will exist in 0, 1, 3, 4, 5, 6, 7, 8, 9
        string num1 = numbers[1];
        char pos6Char;
        for (int c = 0; c < num1.length(); c++)
            {
            pos6Char = num1[c];

            if (ContainsChar(numbers[0], pos6Char) && 
                !ContainsChar(numbers[2], pos6Char) && ContainsChar(numbers[3], pos6Char) && 
                ContainsChar(numbers[4], pos6Char) && ContainsChar(numbers[5], pos6Char) &&
                ContainsChar(numbers[6], pos6Char) && ContainsChar(numbers[7], pos6Char) &&
                ContainsChar(numbers[8], pos6Char) && ContainsChar(numbers[9], pos6Char))
                break;
            }

        pos6 = pos6Char;
        }

    void setPos7(vector<string> numbers)
        {
        // character will exist in 0, 2, 3, 5, 6, 8, 9
        string num2 = numbers[2];
        char pos7Char;
        for (int c = 0; c < num2.length(); c++)
            {
            pos7Char = num2[c];

            if (ContainsChar(numbers[0], pos7Char) && !ContainsChar(numbers[0], pos7Char) &&
                ContainsChar(numbers[3], pos7Char) && 
                !ContainsChar(numbers[4], pos7Char) && ContainsChar(numbers[5], pos7Char) &&
                ContainsChar(numbers[6], pos7Char) && !ContainsChar(numbers[7], pos7Char) &&
                ContainsChar(numbers[8], pos7Char) && ContainsChar(numbers[9], pos7Char))
                break;
            }

        pos6 = pos7Char;
        }

    bool ContainsChar(string chars, char c)
        {
        bool contains = false;
        for (int i = 0; i < chars.length(); i++)
            {
            if (chars[i] == c)
                {
                contains = true;
                break;
                }
            }

        return contains;
        }
    };


class NumberCombos
    {
public:
    vector<CodedNumber> inputs;
    vector<CodedNumber> outputs;
    vector<string> numberStrings;
    NumberGrid* grid;
    int outputSum;

    NumberCombos(string inputs, string outputs)
        {
        convertStringToCodedNumbers(inputs, true);
        convertStringToCodedNumbers(outputs, false);
        
        SetNumberStrings();

        outputSum = 0;
        grid = new NumberGrid(numberStrings);

        SetOutputSum();
        }

private:
    void convertStringToCodedNumbers(string line, bool inputValues)
        {
        vector<CodedNumber> numbers; 

        while (line.length())
            {
            size_t delimiterPos = line.find(" ");
            int delimiterLength = 1;

            string value = line.substr(0, delimiterPos);

            if (value != "")
                {
                CodedNumber* num = new CodedNumber(value);
                numbers.push_back(*num);
                }
        
            // Remove space and used characters
            line.erase(0, delimiterPos + delimiterLength);

            if (delimiterPos == string::npos)
                break;
            }

        if (inputValues)
            this->inputs = numbers;
        else 
            this->outputs = numbers;
        }

    void SetNumberStrings()
        {
        string num0;
        string num1;
        string num2;
        string num3;
        string num4;
        string num5;
        string num6;
        string num7;
        string num8;
        string num9;

        // Get the easy values
        for (int i = 0; i < 10; i++)
            {
            string value = inputs[i].value;

            if (value.length() == 2) // Number 1
                num1 = value;
            else if (value.length() == 4) // Number 4
                num4 = value;
            else if (value.length() == 3) // Number 7
                num7 = value;
            else if (value.length() == 7) // Number 8
                num8 = value;
            }

        // Get the other values
        for (int i = 0; i < 10; i++)
            {
            string value = inputs[i].value;

            if (value.length() == 5) // Number is 2, 3 or 5
                {
                // If all of num1 chars are in value then we know it is 3
                if (ContainsChar(value, num1[0]) && ContainsChar(value, num1[1]))
                    {
                    num3 = value;
                    }
                else 
                    {
                    // num5 will match 3 of num4s chars while num2 will only match 2
                    int numMatches = 0;
                    for (int c = 0; c < 4; c++)
                        {
                        numMatches += ContainsChar(value, num4[c]) ? 1 : 0;
                        }

                    if (numMatches == 3)
                        num5 = value;
                    else 
                        num2 = value;
                    }
                }
            else if (value.length() == 6) // Number is 0, 6 or 9
                {
                // if both num1 chars are found in value then we know it is 0 or 9
                // Which means if either character is NOT found then its a 6
                if (ContainsChar(value, num1[0]) && ContainsChar(value, num1[1]))
                    {
                    // All of 4s characters are in 9 but not all are in 0
                    if (ContainsChar(value, num4[0]) && ContainsChar(value, num4[1]) && 
                        ContainsChar(value, num4[2]) && ContainsChar(value, num4[3]))
                        num9 = value;
                    else 
                        num0 = value;
                    }
                else 
                    {
                    num6 = value;
                    }
                }
            }

        cout << num0 << " " << num1 << " " << num2 << " " << num3 << " " << num4 << " " << num5 << " " << num6 << " " << num7 << " " << num8 << " " << num9 << endl;
        
        numberStrings.push_back(num0);
        numberStrings.push_back(num1);
        numberStrings.push_back(num2);
        numberStrings.push_back(num3);
        numberStrings.push_back(num4);
        numberStrings.push_back(num5);
        numberStrings.push_back(num6);
        numberStrings.push_back(num7);
        numberStrings.push_back(num8);
        numberStrings.push_back(num9);
        }

    void SetOutputSum()
        {
        int val1 = grid->DetermineNumberAttempt2(outputs[0].value);
        int val2 = grid->DetermineNumberAttempt2(outputs[1].value);
        int val3 = grid->DetermineNumberAttempt2(outputs[2].value);
        int val4 = grid->DetermineNumberAttempt2(outputs[3].value);

        cout << outputs[0].value << " " << outputs[1].value << " " << outputs[2].value << " " << outputs[3].value << endl;

        outputSum = (val1 * 1000) + (val2 * 100) + (val3 * 10) + (val4 * 1);

        cout << outputSum << endl;
        }

    bool ContainsChar(string chars, char c)
        {
        bool contains = false;
        for (int i = 0; i < chars.length(); i++)
            {
            if (chars[i] == c)
                {
                contains = true;
                break;
                }
            }

        return contains;
        }
    };

vector<string> getSegment(vector<string> data, bool getInfoSegments)
    {
    vector<string> infoSegments;
    vector<string> decodeSegments;

    for (int i = 0; i < data.size(); i++)
        {
        string line = data[i];
        size_t delimiterPos = line.find("|");
        int delimiterLength = 1;

        infoSegments.push_back(line.substr(0, delimiterPos));

        // remove comma
        line.erase(0, delimiterPos + delimiterLength);

        decodeSegments.push_back(line);
        }
    
    return getInfoSegments ? infoSegments : decodeSegments;
    }

vector<NumberCombos> convertToNumberCombos(vector<string> inputs, vector<string> outputs)
    {
    vector<NumberCombos> numbers; 

    if (inputs.size() != outputs.size())
        cout << "What the heck" << endl;

    for (int i = 0; i < inputs.size(); i++)
        {
        NumberCombos* numCombo = new NumberCombos(inputs[i], outputs[i]);
        numbers.push_back(*numCombo);
        }

    return numbers;
    }

int countValues(vector<CodedNumber> numbers)
    {
    int knownValues = 0; 
    for (int i = 0; i < numbers.size(); i++)
        {
        knownValues += numbers[i].IsSimpleNumber() ? 1 : 0;
        }

    return knownValues;
    }

int sumValues(vector<NumberCombos> numbers)
    {
    int sum = 0; 
    for (int i = 0; i < numbers.size(); i++)
        {
        sum += numbers[i].outputSum;
        }

    return sum;
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

    vector<string> data = util->readFile(FILE_NAME);

    vector<string> inputs = getSegment(data, true);
    vector<string> outputs = getSegment(data, false);

    vector<NumberCombos> dataLines = convertToNumberCombos(inputs, outputs);

    // Add implementation function here
    int result = sumValues(dataLines);

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
