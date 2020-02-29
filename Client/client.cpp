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


void sendStrMessage(string messageSt){
    char mess[messageSt.size()+1];
    strcpy(mess, messageSt.c_str());
    send(sock , mess , strlen(mess), 1024 );
}

void createGraph( string size){
    sendStrMessage("setNodes;"+size+";");
}

void createEdge(string start, string end, string weigth){
    sendStrMessage("addEdge;"+start+";"+end+";"+weigth+";");
}

void end(){
    sendStrMessage("end;");
}

string askAnswer(){
    char buffer[1024] = {0};
    read( sock , buffer, 1024);
    return (string) buffer;
}

string getDijkstra(string src, string dest){
    sendStrMessage("calculate;"+src+";"+dest+";");
    return askAnswer();
}

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


