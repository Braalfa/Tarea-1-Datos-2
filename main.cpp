#include <iostream>
#include <limits>
#include <string>
using namespace std;

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



int main() {
    Graph g = *new Graph();
    g.generateMatrix(9);
    g.addEdge(0,1,4);
    g.addEdge(0,7,8);
    g.addEdge(1,7,11);
    g.addEdge(1,2,8);
    g.addEdge(2,8,2);
    g.addEdge(2,5,4);
    g.addEdge(2,3,7);
    g.addEdge(3,5,14);
    g.addEdge(3,4,9);
    g.addEdge(4,5,10);
    g.addEdge(5,6,2);
    g.addEdge(6,8,6);
    g.addEdge(6,7,1);
    g.addEdge(7,8,7);
    string r=g.dijkstra(0,8);
    printf("%s\n", r.c_str());
}
