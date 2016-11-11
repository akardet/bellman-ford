#ifndef main_h
#define main_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>

using namespace std;

struct Edge
{
    string src, dest;
    int weight;
};

struct Graph
{
    int vertex, edges;
    
    struct Edge* edge;
};

string openFile(int argc, const char * argv[]);
vector <string> splitString(string line);
vector <string> removeNonCharacters(string line);
struct Graph* createGraph(vector<int> graphData);
struct Graph* buildGraph(struct Graph* graph, vector<string> graphString);
vector<int> getVertexEdgeTotals(string data);



#endif /* main_h */
