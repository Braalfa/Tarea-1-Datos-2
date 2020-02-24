// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <cstring>

#include <iostream>
#include <limits>
#include <string>
using namespace std;

#define PORT 8080

void sendIntMessage(int sock, int message){
    char sizeCh[to_string(message).size()+1];
    strcpy(sizeCh, to_string(message).c_str());
    send(sock , sizeCh , strlen(sizeCh) , 0 );

}

void sendStrMessage(int sock,string messageSt){
    char mess[messageSt.size()+1];
    strcpy(mess, messageSt.c_str());
    send(sock , mess , strlen(mess), 0 );
}

void createGraph(int sock, int size){
    sendIntMessage(sock,size);
}

void createEdge(int sock,int start, int end, int weigth){
    sendStrMessage(sock,"continue");
    sendIntMessage(sock, start);
    sendIntMessage(sock, end);
    sendIntMessage(sock,weigth);
}

string getDijkstra(int sock,int src, int dest){

    sendStrMessage(sock,"stop");
    sendIntMessage(sock, src);
    sendIntMessage(sock, dest);

    char buffer[1024] = {0};
    read( sock , buffer, 1024);
    return (string)(buffer);
}

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}


