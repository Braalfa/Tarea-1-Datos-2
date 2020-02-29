#include <string>
using namespace std;

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "Graph.h"

#define PORT 8080


void addEdge(int socket, Graph* g, string message){
    int src,dest, weigth;
    int nodes=g->getNodes();
    int pos;
    try {
        pos=message.find_first_of(";");
        src = stoi(message.substr(0, pos));
        message.erase(0, pos + 1);
        pos=message.find_first_of(";");
        dest = stoi(message.substr(0, pos));
        message.erase(0, pos + 1);
        pos=message.find_first_of(";");
        weigth = stoi(message.substr(0, pos));
        message.erase(0, pos + 1);

        if(nodes>src && nodes>dest && weigth>0 && src >-1 && dest >-1){
            g->addEdge(src,dest,weigth);
            send(socket, "ok", 2, 0);
        }else{
            send(socket, "error", 5, 0);
        }
    }catch(std::exception const & e){
        send(socket, "error", 5, 0);
    }
}

void setNumNodes(int socket, Graph* g, string message){
    int nodes;
    int pos;
    try {
        pos=message.find_first_of(";");
        nodes = stoi(message.substr(0, pos));
        if (nodes > 1) {
            g->generateMatrix(nodes);
            send(socket, "ok", 2, 0);
        } else {
            send(socket, "error", 5, 0);
        }
    } catch (std::exception const & e) {
        send(socket, "error", 5, 0);
    }
}


void calculatePath(int socket, Graph* g, string message){
    int start, end;
    int pos;
    try {
        pos=message.find_first_of(";");
        start = stoi(message.substr(0, pos));
        message.erase(0, pos + 1);
        pos=message.find_first_of(";");
        end = stoi(message.substr(0, pos));
        message.erase(0, pos + 1);

        if (start > -1 && end >-1 && start<g->getNodes() && end<g->getNodes()) {
            string pathSt = g->dijkstra(start, end);
            char path[pathSt.size() + 1];
            strcpy(path, pathSt.c_str());
                send(socket, path, strlen(path), 0);
            } else {
                send(socket, "error", 5, 0);
            }
        } catch (std::exception const & e) {
            send(socket, "error", 5, 0);
        }
    }




void manageCalls(int server_fd, struct sockaddr_in address, int addrlen){
    char buffer[1024];
    bool flag1=true;
    bool flag2=true;
    string message;
    string command;
    int pos;
    int socket;
    Graph* g = new Graph;
    while(flag1){
        socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
        flag2=true;
        while(flag2) {
            read(socket, buffer, 1024);
            message = buffer;
            pos = message.find_first_of(";");
            command = message.substr(0, pos);
            message.erase(0, pos + 1);

            if (command == "setNodes") {
                setNumNodes(socket, g, message);
            } else if (command == "addEdge") {
                addEdge(socket, g, message);
            } else if (command == "calculate") {
                calculatePath(socket, g, message);
            } else if (command == "end") {
                flag2 = false;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

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

    manageCalls( server_fd, address, addrlen);

    return 0;
}

