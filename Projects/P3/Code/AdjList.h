//Kevin Shannon
//Adjacency List Data Structure

#ifndef ADJLIST_H
#define ADJLIST_H

#include <math.h>
#include <climits>
#include <iostream>
#include "LinkedList.h"

class AdjList {
  friend class LinkedList<int>;
  protected:
    LinkedList<int>** adjList;
    int vertices;
  public:
    AdjList(int vertices);
    ~AdjList();
    void AddEdge(int u, int v);
    void Print();
    int LargestDegree();
    void Histogram();
    int MinLen(int* Len, bool* visited);
    int ShortestPath(int u, int v);
    void DFS(int u, bool** visited, int &numNodes);
    void Components();
};

#endif
