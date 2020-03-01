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


/**
 * The class graph is the one that contains the graph and applies dijkstra
 */
class Graph{

private:
    /**
     * Matrix for the graph
     */
    int **matrix;

    /**
     * Array of distances from source when doing dijkstra
     */
    int *distances;
    /**
     * Boolean that indicates if a given node has its shortest path calculated
     */
    bool *added;
    /**
     * Number of nodes in graph
     */
    int nodes;
    /**
     * Array of shortest paths
     */
    string *paths;
    /**
     * Definition of infinite
     */
    int inf=std::numeric_limits<int>::max();

    /**
     * @return void
     * @param start Node to start dijkstra from
     * Method to calculate dijkstra path from a given node
     */
    void fullDijkstra(int start){
        for(int j=0;j<nodes-1;j++) {

            int closest = findMinDistance();
            added[closest] = true;

            for (int i = 0; i < nodes; i++) {
                int distance = matrix[closest][i];
                if (distance < inf && !added[i]  && distances[i] > distances[closest] + distance) {
                    paths[i] = paths[closest] + " "+ to_string(closest);
                    distances[i] = distances[closest] + distance;
                }
            }
        }
    }


    /**
     * @return void
     * @param start Node to start dijkstra from
     * Method no initialize the calculation of best paths
     */
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


    /**
     * @return Number of next node at minimal distance from the origin
     * Method to find the next node at minimal distance from the origin
     */
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
    /**
     * @return Number of nodes on Graph
     * Method to get the number of nodes
     */
    int getNodes(){
        return this->nodes;
    }

    /**
     * @return void
     * Method to add one edge to the graph
     */
    void addEdge(int src, int dest, int weight){
        matrix[src][dest] = weight;
        matrix[dest][src] = weight;
    }

    /**
     * @return void
     * @param nodes Number of nodes for the graph
     * Method to initialize the graph by indicating the number of nodes
     */
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

    /**
     * @param start Node to start from on the path
     * @param end Node destination
     * @return Shortest path from start to end
     *
     * Method to call for the calculus of dijkstra algorithm
     */
    string dijkstra(int start, int end){
        this->initializeDijkstra(start);
        this->fullDijkstra(start);
        if(paths[end].empty()){
            return "No path to destiny";
        }else{
            return paths[end]+" " + to_string(end);
        }
    }



};