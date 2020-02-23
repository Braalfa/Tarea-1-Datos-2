#include <iostream>
#include <limits>
using namespace std;

class Graph{
    int **matrix;
    int *distances;
    bool *added;
    int nodes;
    string *paths;
    int inf=std::numeric_limits<int>::max();


    void addEdge(int src, int dest, int weight){
        matrix[src][dest] = weight;
        matrix[dest][src] = weight;
    }

    void generateMatrix(int nodes){
        this->nodes=nodes;
        matrix = new int*[nodes];

        for (int i = 0; i < nodes; ++i) {
            matrix[i] = new int[nodes];
            for (int j = 0; j < nodes; ++j) {
                matrix[i][j] = std::numeric_limits<int>::max();
            }
        }
    }




};



int main() {
    return 0;
}
