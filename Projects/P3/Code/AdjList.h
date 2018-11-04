//Kevin Shannon
//Templated Adjacency List Data Structure

#ifndef ADJLIST_H
#define ADJLIST_H

#include "LinkedList.h"

template <class T>
class AdjList {
  friend class LinkedList<T>;
  protected:
    LinkedList<T>** adjList;
    int vertices;
  public:
    AdjList(int vertices);
    ~AdjList();
    int indexOf(T id);
    void AddEdge(T u, T v);
    void Print();
};

//AdjList methods

template <class T>
AdjList<T>::AdjList(int vertices) {
  adjList = new LinkedList<T>*[vertices];
  for(int i = 0; i < vertices; i++)
    adjList[i] = new LinkedList<T>();
  this->vertices = vertices;
}

template <class T>
AdjList<T>::~AdjList() {
  for(int i = 0; i < vertices; i++)
    adjList[i]->empty();
  vertices = 0;
}

template <class T>
int AdjList<T>::indexOf(T id) {
  for(int i = 0; i < vertices; i++) {
    if(adjList[i]->getID() == id)
      return i;
    if(adjList[i]->getID() == -1) {
      adjList[i]->setID(id);
      return i;
    }
  }
  return -1;
}

template <class T>
void AdjList<T>::AddEdge(T u, T v) {
  adjList[indexOf(u)]->Append(v);
  adjList[indexOf(v)]->Append(u);
}

template <class T>
void AdjList<T>::Print() {
  for(int i = 0; i < vertices; i++) {
    std::cout << adjList[i]->getID();
    for(int j = 0; j < adjList[i]->Length(); j++)
      std::cout << " " << adjList[i]->Retrieve(j);
    std::cout << std::endl;
  }
}

#endif
