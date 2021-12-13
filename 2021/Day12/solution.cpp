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

using namespace std;

/***DEFINES*******************************************************************/
const string FILE_NAME = "data.txt";

/***GLOBAL VARIABLES**********************************************************/


/***FUNCTION DECLARATIONS*****************************************************/


/***FUNCTION DEFINITIONS******************************************************/
class Path
    {
public:
    string node1;
    string node2;

    Path(string n1, string n2)
        {
        node1 = n1;
        node2 = n2;
        }
    };

class Node
    {
public: 
    string name;
    bool bigCave;
    bool visited;

    Node(string name)
        {
        this-> name = name;
        bigCave = name[0] < 91;   // 90 is captial 'Z'
        visited = false;
        }

private: 
    };

bool isUnique(vector<string> uniqueNodes, string newNode)
    {
    bool isUnique = true;

    for (int i = 0; i < uniqueNodes.size(); i++)
        {
        if (newNode == uniqueNodes[i])
            {
            isUnique = false;
            break;
            }
        }

    return isUnique;
    }

vector<string> getUniqueNodeNames(vector<string> input)
    {
    vector<string> uniqueNodes;

    for (int i = 0; i < input.size(); i++)
        {
        size_t delimiterPos = input[i].find('-');
        int delimiterLength = 1;

        string node1 = input[i].substr(0, delimiterPos);

        if (isUnique(uniqueNodes, node1))
            uniqueNodes.push_back(node1);

        // remove dash
        input[i].erase(0, delimiterPos + delimiterLength);

        string node2 = input[i];

        if (isUnique(uniqueNodes, node2))
            uniqueNodes.push_back(node2);
        }
    }

vector<Node*> createNodes(vector<string> nodeNames)
    {
    vector<Node*> nodes;

    for (int i = 0; i < nodeNames.size(); i++)
        {
        Node* newNode = new Node(nodeNames[i]);
        nodes.push_back(newNode);
        }

    return nodes;
    }

int FindNode(vector<Node*> nodes, string nodeName)
    {
    int i = 0;

    for (; i < nodes.size(); i++)
        {
        if (nodeName == nodes[i]->name)
            break;
        }

    return i;
    }

int CountPaths(vector<Node*> nodes)
    {
    int startIndex = FindNode(nodes, "start");
    Node* startNode = nodes[startIndex];
    
    return 0;
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
    vector<string> nodeNames = getUniqueNodeNames(data);
    vector<Node*> nodes = createNodes(nodeNames);

    // Add implementation function here
    int result = CountPaths(nodes);

    // Report Result
    cout << endl << "Reported Result: " << result << endl;

    return 0;
    }
