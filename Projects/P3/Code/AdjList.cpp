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
  adjList[u]->Append(v);
  adjList[v]->Append(u);
}

void AdjList::Print() {
  for(int i = 0; i < vertices; i++) {
    std::cout << i << " |";
    for(int j = 0; j < adjList[i]->Length(); j++)
      std::cout << " " << adjList[i]->Retrieve(j);
    std::cout << std::endl;
  }
}

int AdjList:: LargestDegree() {
  int largest = 0;
  for(int i = 0; i < vertices; i++) {
    if(largest < adjList[i]->Length())
      largest = adjList[i]->Length();
  }
  return largest;
}

void AdjList::Histogram() {
  int bins = 2*ceil(sqrt(vertices)) + 1;
  int* count = new int[bins];
  int width = 1;
  int maxCount = 0;
  for(int i = 0; i < vertices; i++) {
    for(int j = 0; j < bins; j++) {
      if(adjList[i]->Length() >= j * width && adjList[i]->Length() < (j + 1) * width) {
        count[j]++;
        break;
      }
    }
  }
  for(int i = 0; i < bins; i++) {
    if(count[i] > maxCount)
      maxCount = count[i];
  }
  std::cout << "bins: " << bins << " width: " << width << " maxCount: " << maxCount << std::endl;
  for(int i = maxCount; i >= 0; i--) {
    for(int j = 0; j < bins; j++) {
      if(count[j] >= i)
        std::cout << "*";
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
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
