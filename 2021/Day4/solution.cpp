/*-----------------------------------------------------------------------------
 * solution.cpp
 *
 * 4 Dec 2021	Ryan Stolys
 *
 * ----------------------------------------------------------------------------*/


/***INCLUDES******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../../Utils/utils.cpp"

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/
vector<int> winningBoards_gv;

/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/

class bingoValue
    {
public:
    int value;
    bool found;

    bingoValue(int value)
        {
        this->value = value;
        }
    };

vector<int> getBingoInputs(string inputs)
    {
    vector<int> vectorInputs;

    int firstNum = 0;
    int secondNum = 0;
    int numDigits = 0;
    bool startOfNumber = true;

    for (int i = 0; i < inputs.size(); i++)
        {
        char value = inputs[i];

        if (value == ',')
            {
            // We need to add the previous number
            int number = numDigits == 2 ? firstNum*10 + secondNum : firstNum;
            vectorInputs.push_back(number);

            // Reset values
            firstNum = 0;
            secondNum = 0;
            numDigits = 0;
            startOfNumber = true;
            }
        else 
            {
            numDigits++;
            if (startOfNumber)
                {
                startOfNumber = false;
                firstNum = (int)value - 48;
                }
            else 
                {
                secondNum = (int)value - 48;
                }
            }
        }

    // For final entry
    int number = numDigits == 2 ? firstNum*10 + secondNum : firstNum;
    vectorInputs.push_back(number);

    return vectorInputs;
    }

void printBoardRow(vector<bingoValue> boardRow)
    {
    for (int k = 0; k < boardRow.size(); k++)
        {
        cout << boardRow[k].value << " ";
        }

    cout << endl;
    }

void printVectorRow(vector<int> vectorVals)
    {
    for (int k = 0; k < vectorVals.size(); k++)
        {
        cout << vectorVals[k] << " ";
        }

    cout << endl;
    }

void printBoards(vector< vector< vector<bingoValue> > > boards)
    {
    for (int i = 0; i < boards.size(); i++)
        {
        vector< vector<bingoValue> > singleBoard = boards[i];
        for (int j = 0; j < singleBoard.size(); j++)
            {
            printBoardRow(singleBoard[j]);
            }
        cout << endl;
        }
    }


vector<bingoValue> getSingleBoardRow(string input)
    {
    vector<bingoValue> vectorInputs;

    int firstNum = 0;
    int secondNum = 0;
    
    for (int i = 0; i < input.size(); i += 3)
        {
        char value1 = input[i];
        char value2 = input[i+1];

        if (value1 == ' ')
            firstNum = 0;
        else 
            firstNum = (int)value1 - 48;

        secondNum = (int)value2 - 48;

        int value = firstNum*10 + secondNum;

        bingoValue* boardItem = new bingoValue(value);
        vectorInputs.push_back(*boardItem);
        }

    return vectorInputs;
    }

vector< vector< vector<bingoValue> > > generateBoards(vector<string> data)
    {
    // first line of data is game board
    // game boards are 5x5
    vector< vector< vector<bingoValue> > > boards;
    
    for (int i = 0; i < data.size() - 4; i += 6)
        {
        vector< vector<bingoValue> > singleBoard;

        vector<bingoValue> row1 = getSingleBoardRow(data[i]);
        vector<bingoValue> row2 = getSingleBoardRow(data[i+1]);
        vector<bingoValue> row3 = getSingleBoardRow(data[i+2]);
        vector<bingoValue> row4 = getSingleBoardRow(data[i+3]);
        vector<bingoValue> row5 = getSingleBoardRow(data[i+4]);

        singleBoard.push_back(row1);
        singleBoard.push_back(row2);
        singleBoard.push_back(row3);
        singleBoard.push_back(row4);
        singleBoard.push_back(row5);

        boards.push_back(singleBoard);
        }

    return boards;
    }

bool checkForCompletedRow(vector< vector<bingoValue> > board)
    {
    bool rowCompleted = false;
    for (int i = 0; i < board.size(); i++)
        {
        bool allFound = true;
        for (int j = 0; j < 5; j++)
            {
            if (!board[i][j].found)
                allFound = false;
            }

        if (allFound)
            rowCompleted = true;
        }

    return rowCompleted;
    }

bool checkForCompletedColumn(vector< vector<bingoValue> > board)
    {
    // We know the board is 5x5
    bool columnCompleted = false;

    for (int i = 0; i < board.size(); i++)
        {
        bool allFound = true;
        for (int j = 0; j < 5; j++)
            {
            if (!board[j][i].found)
                allFound = false;
            }

        if (allFound)
            columnCompleted = true;
        }

    return columnCompleted;
    }

int checkForWinner(vector< vector< vector<bingoValue> > > boards)
    {
    int winningBoard = -1;

    for (int i = 0; i < boards.size(); i++)
        {
        if (checkForCompletedRow(boards[i]))
            {
            cout << "Has winning row" << endl;
            winningBoard = i;
            break;
            }   
        else if (checkForCompletedColumn(boards[i]))
            {
            cout << "Has winning column" << endl;
            winningBoard = i;
            break;
            }
        }

    return winningBoard;
    }

int checkForLooser(vector< vector< vector<bingoValue> > > boards)
    {
    bool singleLosingBoard = false;
    int losingBoardIndex = -1;
    int numBoards = boards.size();

    for (int i = 0; i < boards.size(); i++)
        {
        // No need to check boards that have already won
        if (find(winningBoards_gv.begin(), winningBoards_gv.end(), i) != winningBoards_gv.end())
            continue;

        if (checkForCompletedRow(boards[i]))
            {
            cout << "Board #" << i << " won" << endl;
            winningBoards_gv.push_back(i);
            }  
        else if (checkForCompletedColumn(boards[i]))
            {
            cout << "Board #" << i << " won" << endl;
            winningBoards_gv.push_back(i);
            }

        if (winningBoards_gv.size() + 1 >= numBoards)
            {
            sort(winningBoards_gv.begin(), winningBoards_gv.end());
            singleLosingBoard = true;
            break;
            }
        }

    if (singleLosingBoard)
        {
        //printVectorRow(winningBoards_gv);
        int lastIndex = winningBoards_gv[0];
        for (int i = 1; i < winningBoards_gv.size(); i++)
            {
            // We should have all the numbers in order
            if ((lastIndex + 1) != winningBoards_gv[i])
                {
                losingBoardIndex = lastIndex + 1;
                //cout << "Index: " << losingBoardIndex << endl;
                break;
                }

            lastIndex = winningBoards_gv[i];
            }
        }

    return losingBoardIndex;
    }

vector< vector< vector<bingoValue> > > clearWinners(vector< vector< vector<bingoValue> > > boards)
    {
    vector<int> winningIndexes;
    int numBoards = boards.size();

    for (int i = 0; i < boards.size(); i++)
        {
        if (checkForCompletedRow(boards[i]))
            {
            cout << "Board #" << i << " won" << endl;
            winningIndexes.push_back(i);
            }  
        else if (checkForCompletedColumn(boards[i]))
            {
            cout << "Board #" << i << " won" << endl;
            winningIndexes.push_back(i);
            }
        }

    // Sort a loop through backwards to avoid ruining ordering
    sort(winningIndexes.begin(), winningIndexes.end());
    for (int i = winningIndexes.size() - 1; i >= 0; i--)
        {
        boards.erase(boards.begin() + winningIndexes[i]);
        }

    return boards;
    }


vector< vector< vector<bingoValue> > > markFoundItems(vector< vector< vector<bingoValue> > > boards, int calledValue)
    {   
    // For each board 
    for (int i = 0; i < boards.size(); i++)
        {
        // For each row
        for (int j = 0; j < boards[i].size(); j++)
            {
            // For each item
            for (int k = 0; k < boards[i][j].size(); k++)
                {
                if (boards[i][j][k].value == calledValue) 
                    boards[i][j][k].found = true;
                }
            }
        }

    return boards;
    }

int computeWinningResult(vector< vector<bingoValue> > board, int finalValue)
    {
    int notFoundSum = 0;

    // For each row
    for (int j = 0; j < board.size(); j++)
        {
        // For each item
        for (int k = 0; k < board[j].size(); k++)
            {
            if (!board[j][k].found) 
                notFoundSum += board[j][k].value;
            }
        }

    return notFoundSum * finalValue;
    }

int findWinningBoard(vector< vector< vector<bingoValue> > > boards, vector<int> inputs)
    {
    vector< vector<bingoValue> > winningBoard;
    int finalValue = -1;

    for (int i = 0; i < inputs.size(); i++)
        {
        boards = markFoundItems(boards, inputs[i]);

        int winningBoardIndex = checkForWinner(boards);

        if (winningBoardIndex != -1)
            {
            finalValue = inputs[i];
            winningBoard = boards[winningBoardIndex];
            break;
            }
        }

    vector< vector< vector<bingoValue> > > temp; 
    temp.push_back(winningBoard);
    printBoards(temp);

    cout << finalValue << endl;

    // Compute result
    return computeWinningResult(winningBoard, finalValue);
    }


int findLastWinningBoard(vector< vector< vector<bingoValue> > > boards, vector<int> inputs)
    {
    vector< vector<bingoValue> > lastLosingBoard;
    int finalValue = -1;

    int i;
    for (i = 0; i < inputs.size(); i++)
        {
        boards = markFoundItems(boards, inputs[i]);

        boards = clearWinners(boards);

        if (boards.size() <= 1)
            {
            break;
            }
        }
    
    for ( ; i < inputs.size(); i++)
        {
        // mark the items found
        boards = markFoundItems(boards, inputs[i]);

        // Looking for when our last board wins
        int boardWon = checkForWinner(boards);

        if (boardWon != -1)
            {
            lastLosingBoard = boards[boardWon];
            finalValue = inputs[i];
            break;
            }        
        }

    cout << endl << "Losing Board" << endl;
    printBoards(boards);

    cout << "finalValue: " << finalValue << endl;

    // Compute result
    return computeWinningResult(lastLosingBoard, finalValue);
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

    // Get data
    vector<string> data = util->readFile(FILE_NAME);
    string inputs = data[0];

    vector<int> bingoInputs = getBingoInputs(inputs);

    // erase first two lines (inputs and blank line)
    data.erase(data.begin());
    data.erase(data.begin());

    // Create bingo boards
    vector< vector< vector<bingoValue> > > boards = generateBoards(data);

    // Add implementation function here
    //int result = findWinningBoard(boards, bingoInputs); 
    int result = findLastWinningBoard(boards, bingoInputs);

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
