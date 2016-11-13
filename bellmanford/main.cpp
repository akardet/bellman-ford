#include "header.hpp"

int main(int argc, const char * argv[]) {
    
    string file_content;
    vector<string> splitData;
    vector<int> graphTotals;
    
    //read file into a string
    file_content = openFile(argc, argv);
    
    cout << "one" << endl;
    
    //remove special characters from string
    splitData = splitString(file_content);
    
    cout << "two" << endl;
    
    //determine number of total vertices and edges
    graphTotals = getVertexEdgeTotals(file_content);
    
    cout << "three" << endl;
    
    //create graph
    struct Graph* graph = createGraph(graphTotals);
    
    graph = buildGraph(graph, splitData);
    
    bellmanford(graph);
    
    free(graph);
    
    
    
    return 0;
}
