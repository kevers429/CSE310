//Kevin Shannon
//usage: ./p3 < file

#include <iostream>
#include <string.h>
#include <iomanip>
#include "AdjList.h"

using namespace std;

int vertices, edges, u, v, numCommands;
string commandName;

int main() {
  cin >> vertices >> edges;
  AdjList* network = new AdjList(vertices, edges);
  for(int i = 0; i < edges; i++) {
    cin >> u >> v;
    network->AddEdge(u, v);
  }
  cin >> numCommands;
  for(int i = 0; i < numCommands; i++) {
    cin >> commandName;
    if(commandName == "degree-distribution")
      network->Histogram();
    else if(commandName == "components")
      network->Components();
    else if(commandName == "shortest-path") {
      cin >> u >> v;
      network->ShortestPath(u, v);
    }
    else if(commandName == "diameter")
      cout << "diameter: " << network->Diameter() << endl;
    else if(commandName == "spanning-tree")
      network->Kruskal();
  }
  delete network;
  return 0;
}
