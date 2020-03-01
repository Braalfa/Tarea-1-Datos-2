#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

#endif // CLIENT_H

/**
 * Initiates the client, connects to the server
 */
int initiateClient();
/**
 * Tells the server to calculate the shortest path
 * @param src Start node
 * @param dest End node
 * @return Shortest path
 */
string getDijkstra(string src, string dest);
/**
 * Tells the server to create an edge
 * @param start  Node to start from
 * @param end Node to get to
 * @param weigth Weigth of the edge
 */
void createEdge(string start, string end, string weigth);
/**
 * Tells server to create graph
 * @param size Number of nodes for the graph
 */
void createGraph(string size);
/**
 * Sends string message to socket
 * @param messageSt message
 */
void sendStrMessage(string messageSt);
/**
 * Waits for answer from server
 * @return  Answer from server
 */
string askAnswer()
/**
 * Tells server to end the connection
 */
void end();
