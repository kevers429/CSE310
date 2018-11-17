//AdjList methods
#include "AdjList.h"

AdjList::AdjList(int vertices) {
  adjList = new LinkedList<int>*[vertices];
  for(int i = 0; i < vertices; i++)
    adjList[i] = new LinkedList<int>();
  this->vertices = vertices;
}

AdjList::~AdjList() {
  for(int i = 0; i < vertices; i++)
    adjList[i]->Empty();
  vertices = 0;
}

void AdjList::AddEdge(int u, int v) {
  if(u == v)
    return;
  adjList[u]->Append(v);
  adjList[v]->Append(u);
}

int AdjList::LargestDegree() {
  int largest = 0;
  for(int i = 0; i < vertices; i++) {
    if(largest < adjList[i]->Length())
      largest = adjList[i]->Length();
  }
  return largest;
}

std::string AdjList::RangeHelper(int i) {
    std::ostringstream oss;
    oss << i << "-" << LargestDegree();
    return oss.str();
}

void AdjList::Histogram() {
  int count[vertices];
  for(int i = 0; i < vertices; i++)
    count[i] = 0;
  bool smush = false;
  for(int i = 0; i < vertices; i++)
    count[adjList[i]->Length()]++;
  for(int i = 1; i <= LargestDegree(); i++) {
     if(!smush) {
      if(count[i] == 0 && count[i+1] == 0 && count[i+2] == 0) {
        smush = true;
        std::cout << std::setw(10) << std::left << RangeHelper(i);
      } else
        std::cout << std::setw(10) << std::left << i;
    }
    for(int j = 0; j < count[i]; j++) {
      if(count[i] > 100)  {
        if(j % 20 == 0)
          std::cout << "#";
      }
      else
        std::cout << "*";
    }
    if(!smush)
      std::cout << std::endl;
  }
  std::cout << std::endl;
}

void AdjList::Components() {
  int components = 0;
  bool* visited = new bool[vertices];
  for(int i = 0; i < vertices; i++)
    visited[i] = false;
  for(int i = 0; i < vertices; i++) {
    if(!visited[i]) {
      int numNodes = 0;
      DFS(i, &visited, numNodes);
      components++;
      std::cout << "component #" << components << ": " << numNodes << std::endl;
    }
  }
  std::cout << "total components: " << components << std ::endl;
  delete[] visited;
}

int AdjList::MinLen(int* Len, bool* visited) {
  int min = INT_MAX;
  int pos;
  for(int i = 0; i < vertices; i++) {
    if(visited[i] == false && Len[i] < min) {
      min = Len[i];
      pos = i;
    }
  }
  return pos;
}

int AdjList::ShortestPath(int u, int v) {
  int Len[vertices];
  bool visited[vertices];
  for(int i = 0; i < vertices; i++) {
    visited[i] = false;
    Len[i] = INT_MAX;
  }
  Len[u] = 0;
  while(!visited[v]) {
    int s = MinLen(Len, visited);
    visited[s] = true;
    for(int i = 0; i < vertices; i++) {
      if(!visited[i] && Len[s] + 1 < Len[i] && adjList[s]->Contains(i))
        Len[i] = Len[s] + 1;
    }
  }
  return Len[v];
}

void AdjList::DFS(int u, bool** visited, int &numNodes) {
  (*visited)[u] = true;
  numNodes++;
  for(int i = 0; i < adjList[u]->Length(); i++) {
    if(!(*visited)[adjList[u]->Retrieve(i)])
      DFS(adjList[u]->Retrieve(i), visited, numNodes);
  }
}
