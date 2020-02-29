#include <iostream>
#include <limits>
#include <string>
using namespace std;

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <cstring>



class Graph{

private:
    int **matrix;
    int *distances;
    bool *added;
    int nodes;
    string *paths;
    int inf=std::numeric_limits<int>::max();

    void fullDijkstra(int start);
    void initializeDijkstra(int start);
    int findMinDistance();

public:
    int getNodes();
    void addEdge(int src, int dest, int weight);
    void generateMatrix(int nodes);
    string dijkstra(int start, int end);



};