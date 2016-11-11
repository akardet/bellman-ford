#include "header.hpp"


string openFile(int argc, const char * argv[]) {
    string data;
    
    //check if user passed filename
    if (argc != 2)
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    else {
        ifstream FILE (argv[1]);
        
        //check if file opened properly
        if (!FILE.is_open())
            cout << "Could not open file\n";
        else {
            string str;
            vector<string> parsedString;
            while(getline(FILE, str)) {
                data += str;
                data.push_back('\n');
            }
        }
        
        FILE.close();
    }
    
    return data;
}


vector <string> splitString(string line) {
    vector<string> v ; //Use vector to add the words
    
    size_t prev_pos = 0, pos;
    while ((pos = line.find_first_of("\n", prev_pos)) != string::npos)
    {
        if (pos > prev_pos)
            v.push_back(line.substr(prev_pos, pos-prev_pos));
        prev_pos= pos+1;
    }
    if (prev_pos < line.length())
        v.push_back(line.substr(prev_pos, string::npos));
    
    return v;
    
}

vector <string> removeNonCharacters(string line) {
    vector<string> v ; //Use vector to add the words
    
    size_t prev_pos = 0, pos;
    while ((pos = line.find_first_of(";(), ", prev_pos)) != string::npos)
    {
        if (pos > prev_pos)
            v.push_back(line.substr(prev_pos, pos-prev_pos));
        prev_pos= pos+1;
    }
    if (prev_pos < line.length())
        v.push_back(line.substr(prev_pos, string::npos));
    
    return v;
    
}

struct Graph* createGraph(vector<int> graphData) {
    
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vertex = graphData[0];
    graph->edges = graphData[1];
    
    return graph;
}

struct Graph* buildGraph(struct Graph* graph, vector<string> graphString) {
    int edgeCount = 0;
    
    for(int i = 0; i <= graphString.size()-1; i++) {
        vector<string> parsedVertexString;
        string vertexString = graphString[i];
        
        parsedVertexString = removeNonCharacters(vertexString);
        string headVertex = parsedVertexString[0];
        
        graph->edge = new Edge[graph->edges];
        for(int j = 1; j < parsedVertexString.size()-1; j+=2) {
            graph->edge[edgeCount].src = headVertex;
            graph->edge[edgeCount].dest = parsedVertexString[j];
            graph->edge[edgeCount].weight = stoi(parsedVertexString[j+1]);
            edgeCount++;
        }
        
    }
    
    cout << graph->edge[8].src << " " << graph->edge[8].dest << " " << graph->edge[8].weight << endl;
    
    
    return graph;
}

vector<int> getVertexEdgeTotals(string data) {
    vector<int> graphTotals;
    size_t vertexTotal = count(data.begin(), data.end(), '\n');
    size_t edgeTotal = count(data.begin(), data.end(), ';');
    
    graphTotals.push_back(static_cast<int>(vertexTotal));
    graphTotals.push_back(static_cast<int>(edgeTotal));
    
    return graphTotals;
}
