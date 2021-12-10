/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * ?? Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>    // std::sort

#include <fstream>
#include "../../Utils/file.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/
const char ROUNDED_OPEN = '(';
const char SQUARE_OPEN = '[';
const char CURLY_OPEN = '{';
const char TRI_OPEN = '<';

const char ROUNDED_CLOSE = ')';
const char SQUARE_CLOSE = ']';
const char CURLY_CLOSE = '}';
const char TRI_CLOSE = '>';

const int R_SCORE = 3;
const int S_SCORE = 57;
const int C_SCORE = 1197;
const int T_SCORE = 25137;

const int R_SCORE_C = 1;
const int S_SCORE_C = 2;
const int C_SCORE_C = 3;
const int T_SCORE_C = 4;

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class Chunk
    {
public:
    string line;
    bool isInvalid;
    char invalidChar;
    long completionScore;

    Chunk(string line)
        {
        this->line = line;
        isInvalid = false;
        CheckValidity();
        CompleteLine();
        }

    int GetScore()
        {
        int score = 0;

        if (isInvalid)
            {
            if (invalidChar == ROUNDED_CLOSE)
                score = R_SCORE;
            else if (invalidChar == CURLY_CLOSE)
                score = C_SCORE;
            else if (invalidChar == TRI_CLOSE)
                score = T_SCORE;
            else if (invalidChar == SQUARE_CLOSE)
                score = S_SCORE;
            }

        return score;
        }

private:
    void CompleteLine()
        {
        if (isInvalid)
            return;

        long score = 0;
        vector<char> brackets;

        for (int i = 0; i < line.length(); i++)
            {
            char c = line[i];
            if (c == ROUNDED_OPEN || c == CURLY_OPEN || c == SQUARE_OPEN || c == TRI_OPEN)
                brackets.push_back(c);
            else 
                {
                char expected = brackets.back();
                brackets.pop_back();
                }
            }

        // Compute the score to complete this line
        for (int i = brackets.size() - 1; i >= 0; i--)
            {
            char c = brackets[i];

            if (c == ROUNDED_OPEN)
                {
                score *= 5;
                score += R_SCORE_C;
                }
            else if (c == CURLY_OPEN)
                {
                score *= 5;
                score += C_SCORE_C;
                }
            else if (c ==SQUARE_OPEN)
                {
                score *= 5;
                score += S_SCORE_C;
                }
            else if (c == TRI_OPEN)
                {
                score *= 5;
                score += T_SCORE_C;
                }
            }

        completionScore = score;
        }


    void CheckValidity()
        {
        vector<char> brackets;

        for (int i = 0; i < line.length(); i++)
            {
            char c = line[i];
            if (c == ROUNDED_OPEN || c == CURLY_OPEN || c == SQUARE_OPEN || c == TRI_OPEN)
                brackets.push_back(c);
            else 
                {
                char expected = brackets.back();
                brackets.pop_back();

                if (c == ROUNDED_CLOSE && expected != ROUNDED_OPEN)
                    {
                    isInvalid = true;
                    invalidChar = c;
                    break;
                    }
                else if (c == CURLY_CLOSE && expected != CURLY_OPEN)
                    {
                    isInvalid = true;
                    invalidChar = c;
                    break;
                    }
                else if (c == SQUARE_CLOSE && expected != SQUARE_OPEN)
                    {
                    isInvalid = true;
                    invalidChar = c;
                    break;
                    }
                else if (c == TRI_CLOSE && expected != TRI_OPEN)
                    {
                    isInvalid = true;
                    invalidChar = c;
                    break;
                    }
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

    vector<Chunk> chunks;
    for (int i = 0; i < data.size(); i++)
        {
        Chunk* newChunk = new Chunk(data[i]);
        chunks.push_back(*newChunk);
        }

    // int score = 0;
    // for (int i = 0; i < data.size(); i++)
    //     {
    //     score += chunks[i].GetScore();
    //     }

    // Only take ones that are not corrupt
    vector<Chunk> incompleteChunks;
    for (int i = 0; i < chunks.size(); i++)
        {
        if (!chunks[i].isInvalid)
            incompleteChunks.push_back(chunks[i]);
        }

    vector<long> scores;
    for (int i = 0; i < incompleteChunks.size(); i++)
        {
        scores.push_back(incompleteChunks[i].completionScore);
        }

    sort(scores.begin(), scores.end());

    int middleScoreIndex = scores.size() / 2;
    cout << middleScoreIndex << endl;
    cout << scores[middleScoreIndex] << endl;

    // for (int i = 0; i < scores.size(); i++)
    //     {
    //     cout << scores[i] << endl;
    //     }

    // Add implementation function here
    int result = 0;

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
