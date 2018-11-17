//Kevin Shannon
//Adjacency List Data Structure

#ifndef ADJLIST_H
#define ADJLIST_H

#include <math.h>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "LinkedList.h"

class AdjList {
  friend class LinkedList<int>;
  protected:
    LinkedList<int>** adjList;
    int vertices;
    std::string RangeHelper(int i);
    int LargestDegree();
    int MinLen(int* Len, bool* visited);
    void DFS(int u, bool** visited, int &numNodes);
  public:
    AdjList(int vertices);
    ~AdjList();
    void AddEdge(int u, int v);
    void Histogram();
    void Components();
    int ShortestPath(int u, int v);
};

#endif
