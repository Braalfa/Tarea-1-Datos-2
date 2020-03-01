//
// Created by bryan on 1/3/20.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#include <string>
using namespace std;

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "Graph.h"

#define PORT 8080


/**
 * @param socket The socket number
 * @param g The graph
 * @param message The message send by the client
 * @return Sends path to client
 *
 * Adds an edge to the graph
 */
void addEdge(int socket, Graph* g, string message);


/**
 * @param socket The socket numer
 * @param g The graph
 * @param message The message send by the client
 * @return void
 *
 * Method to set the number of nodes of the graph
 */
void setNumNodes(int socket, Graph* g, string message);

/**
 * @param socket The socket numer
 * @param g The graph
 * @param message The message send by the client
 * @return Sends path to client
 *
 * Method to calculate shortest path
 */
void calculatePath(int socket, Graph* g, string message);

/**
 * @return void
 * Method to manage the messages send by the client
 */
void manageCalls(int server_fd, struct sockaddr_in address, int addrlen);


int main(int argc, char const *argv[]);



#endif //UNTITLED_SERVER_H

