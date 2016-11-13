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
    graph->edge = new Edge[graph->edges];
    
    for(int i = 0; i <= graphString.size()-1; i++) {
        vector<string> parsedVertexString;
        string vertexString = graphString[i];
        
        parsedVertexString = removeNonCharacters(vertexString);
        string headVertex = parsedVertexString[0];
        
        for(int j = 1; j < parsedVertexString.size()-1; j+=2) {
            graph->edge[edgeCount].src = headVertex;
            graph->edge[edgeCount].dest = parsedVertexString[j];
            graph->edge[edgeCount].weight = stoi(parsedVertexString[j+1]);
            edgeCount++;
        }
        
    }
    
    
    return graph;
}

void bellmanford(struct Graph* graph) {
    int V = graph->vertex;
    int E = graph->edges;
    vector<string> vertexKey;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[0] = 0;

    vertexKey = populateKey(graph);
    
    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = getPosition(graph->edge[j].src, vertexKey, E);
            int v = getPosition(graph->edge[j].dest, vertexKey, E);
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    
    for (int i = 0; i < E; i++)
    {
        int u = getPosition(graph->edge[i].src, vertexKey, E);
        int v = getPosition(graph->edge[i].dest, vertexKey, E);
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
    
    printGraph(dist, V, vertexKey);
}

vector<string> populateKey(struct Graph* graph) {
    int j = 0;
    int i = 0;
    vector<string> key;
    
    while (i < graph->edges) {
        if (key.empty()) {
            key.push_back(graph->edge[i].src);
        }
        else if (key[j] == graph->edge[i].src) {}
        else {
            key.push_back(graph->edge[i].src);
            j++;
        }
        
        i++;
    }
    
    return key;

}

int getPosition(string vertex, vector<string> keys, int totalEdges) {
    for (int i = 0; i < totalEdges; i++) {
        if(keys[i] == vertex)
            return i;
    }
    
    return -1;
}

vector<int> getVertexEdgeTotals(string data) {
    vector<int> graphTotals;
    size_t vertexTotal = count(data.begin(), data.end(), '\n');
    size_t edgeTotal = count(data.begin(), data.end(), ';');
    
    graphTotals.push_back(static_cast<int>(vertexTotal));
    graphTotals.push_back(static_cast<int>(edgeTotal));
    
    return graphTotals;
}

void printGraph(int dist[], int totalVertices, vector<string> keys) {
    for (int i = 0; i < totalVertices; ++i)
        cout << keys[i] << " | " << dist[i] << endl;
}
