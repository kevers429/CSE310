//Kevin Shannon
//usage: ./p2 < file

#include <iostream>
#include <string.h>
#include <iomanip>
#include "AdjList.h"

using namespace std;

int vertices, edges, u, v;


int main() {
  cin >> vertices >> edges;
  AdjList<int>* network = new AdjList<int>(vertices);
  for(int i = 0; i < edges; i++) {
    cin >> u >> v;
    network->AddEdge(u, v);
  }
  
  return 0;
}
