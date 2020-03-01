// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>

#include <string>
using namespace std;

#define PORT 8080

int sock=0;

/**
 * Sends string message to socket
 * @param messageSt message
 */
void sendStrMessage(string messageSt){
    char mess[messageSt.size()+1];
    strcpy(mess, messageSt.c_str());
    send(sock , mess , strlen(mess), 1024 );
}

/**
 * Tells server to create graph
 * @param size Number of nodes for the graph
 */
void createGraph( string size){
    sendStrMessage("setNodes;"+size+";");
}

/**
 * Tells the server to create an edge
 * @param start  Node to start from
 * @param end Node to get to
 * @param weigth Weigth of the edge
 */
void createEdge(string start, string end, string weigth){
    sendStrMessage("addEdge;"+start+";"+end+";"+weigth+";");
}

/**
 * Tells server to end the connection
 */
void end(){
    sendStrMessage("end;");
}

/**
 * Waits for answer from server
 * @return  Answer from server
 */
string askAnswer(){
    char buffer[1024] = {0};
    read( sock , buffer, 1024);
    return (string) buffer;
}

/**
 * Tells the server to calculate the shortest path
 * @param src Start node
 * @param dest End node
 * @return Shortest path
 */
string getDijkstra(string src, string dest){
    sendStrMessage("calculate;"+src+";"+dest+";");
    return askAnswer();
}

/**
 * Initiates the client, connects to the server
 */
void initiateClient()
{
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}


