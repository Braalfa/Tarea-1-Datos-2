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
#include "Graph.h"

#define PORT 8080




int support() {
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

void connectToGraph(int new_socket, char buffer[1024]){
    read( new_socket , buffer, 1024);
    Graph* g = new Graph();
    g->generateMatrix(atoi(buffer));

    read( new_socket , buffer, 1024);
    string finish= buffer;
    int src,dest, weigth, start, end;

    while(finish == "continue" ){
        read( new_socket , buffer, 1024);
        src=atoi(buffer);
        read( new_socket , buffer, 1024);
        dest=atoi(buffer);
        read( new_socket , buffer, 1024);
        weigth=atoi(buffer);
        read( new_socket , buffer, 1024);
        finish=buffer;
        g->addEdge(src,dest,weigth);
    }

    read( new_socket , buffer, 1024);
    start=atoi(buffer);
    read( new_socket , buffer, 1024);
    end=atoi(buffer);

    string pathSt=g->dijkstra(start, end);
    char path[pathSt.size()+1];
    strcpy(path, pathSt.c_str());
    printf("%s\n",buffer );
    send(new_socket , path , strlen(path), 0 );
    printf("Hello message sent\n");
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("Socket has failed");
        exit(EXIT_FAILURE);
    }

    bool socketToPort= setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt));
    if (socketToPort)
    {
        perror("Port not asigned to the socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    int bindResult = bind(server_fd, (struct sockaddr *)&address,sizeof(address));
    if (bindResult<0)
    {
        perror("Bind has failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("Listening has failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("Aceptance has failed");
        exit(EXIT_FAILURE);
    }

    connectToGraph(new_socket,buffer);
    return 0;
}

