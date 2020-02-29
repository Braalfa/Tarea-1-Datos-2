#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

#endif // CLIENT_H


int initiateClient();
string getDijkstra(string src, string dest);
void createEdge(string start, string end, string weigth);
void createGraph(string size);
void sendStrMessage(string messageSt);
void sendIntMessage(int message);
string askAnswer();
void end();
