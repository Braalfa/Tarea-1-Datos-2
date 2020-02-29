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

    void fullDijkstra(int start){
        for(int j=0;j<nodes-1;j++) {

            int closest = findMinDistance();
            added[closest] = true;

            for (int i = 0; i < nodes; i++) {
                int distance = matrix[closest][i];
                if (distance < inf && !added[i]  && distances[i] > distances[closest] + distance) {
                    paths[i] = paths[closest] + " " + to_string(closest);
                    distances[i] = distances[closest] + distance;
                }
            }
        }
    }

    void initializeDijkstra(int start){
        distances = new int[nodes];
        paths = new string[nodes];
        added = new bool[nodes];

        for (int i = 0; i < nodes; i++) {
            distances[i]=matrix[start][i];
            if(distances[i]<inf){
                paths[i]= to_string(start);
            }else{
                paths[i]= "";
            }
        }

        for(int i=0;i<nodes;i++){
            added[i]=false;
        }
        added[start]= true;

    }

    int findMinDistance(){
        int min= distances[0];
        int currentMin = 0;
        for(int i=0;i< nodes; i++){
            if(distances[i]<min && !added[i]){
                min=distances[i];
                currentMin=i;
            }
        }
        return currentMin;
    }

public:
    int getNodes(){
        return this->nodes;
    }

    void addEdge(int src, int dest, int weight){
        matrix[src][dest] = weight;
        matrix[dest][src] = weight;
    }

    void generateMatrix(int nodes){
        this->nodes=nodes;
        matrix = new int*[nodes];

        for (int i = 0; i < nodes; i++) {
            matrix[i] = new int[nodes];
            for (int j = 0; j < nodes; j++) {
                matrix[i][j]= std::numeric_limits<int>::max();
            }
        }
    }

    string dijkstra(int start, int end){
        this->initializeDijkstra(start);
        this->fullDijkstra(start);
        if(paths[end].empty()){
            return "No path to destiny";
        }else{
            return paths[end];
        }
    }



};