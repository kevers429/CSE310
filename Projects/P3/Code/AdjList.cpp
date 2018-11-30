//AdjList methods
#include "AdjList.h"

AdjList::AdjList(int vertices, int edges) { //Default constructor
  adjList = new LinkedList<int>*[vertices]; //creates array of linked lists
  for(int i = 0; i < vertices; i++)
    adjList[i] = new LinkedList<int>();
  this->vertices = vertices;
  this->edges = edges;
}

AdjList::~AdjList() { //DESTORY!
  for(int i = 0; i < vertices; i++)
    delete adjList[i]; //no memory leaks here
  delete[] adjList;
  vertices = 0;
}

void AdjList::AddEdge(int u, int v) { //adds new edge to adjList
  if(u == v) //self loops are a no no
    return;
  this->adjList[u]->Append(v);
  this->adjList[v]->Append(u);
}

int AdjList::LargestDegree() { //returns the largest degree vertex
  int largest = 0;
  for(int i = 0; i < vertices; i++) {
    if(largest < adjList[i]->Length())
      largest = adjList[i]->Length();
  }
  return largest;
}

std::string AdjList::RangeHelper(int i) { //only for standardizing width of output
    std::ostringstream oss;
    oss << i << "-" << LargestDegree();
    return oss.str();
}

void AdjList::Histogram() {
  int count[vertices]; //holds the number of verticies with degree equal to its index
  for(int i = 0; i < vertices; i++)
    count[i] = 0;
  bool smush = false;
  for(int i = 0; i < vertices; i++)
    count[adjList[i]->Length()]++; //add it to the list!
  for(int i = 1; i <= LargestDegree(); i++) {
     if(!smush) {
      if(count[i] == 0 && count[i+1] == 0 && count[i+2] == 0) { //three empty bins in a row
        smush = true;
        std::cout << std::setw(10) << std::left << RangeHelper(i);
      } else
        std::cout << std::setw(10) << std::left << i;
    }
    for(int j = 0; j < count[i]; j++) {
      if(count[i] > 100)  {
        if(j % 20 == 0) //if more that 100 use # to represent groups of 20
          std::cout << "#";
      }
      else
        std::cout << "*";
    }
    if(!smush) //dont put a newline, if we're smushing
      std::cout << std::endl;
  }
  std::cout << std::endl;
}

void AdjList::Components() {
  int components = 0;
  bool* visited = new bool[vertices]; //keeps track of we're we've been
  for(int i = 0; i < vertices; i++)
    visited[i] = false;
  for(int i = 0; i < vertices; i++) {
    if(!visited[i]) { //new vertex
      int numNodes = 0;
      DFS(i, &visited, numNodes); //do a depth first search to find all the verticies we can
      components++; //for each DFS there is anotehr component
      std::cout << "component #" << components << " size: " << numNodes << std::endl;
    }
  }
  std::cout << "total components: " << components << std ::endl;
  delete[] visited;
}


void AdjList::DFS(int u, bool** visited, int &numNodes) {
  (*visited)[u] = true;
  numNodes++;
  for(int i = 0; i < adjList[u]->Length(); i++) { //for each adjacent vertex
    if(!(*visited)[adjList[u]->Retrieve(i)]) //if we haven't been yet, GO!
      DFS(adjList[u]->Retrieve(i), visited, numNodes);
  }
}

int AdjList::MinLen(int* Len, bool* visited) { //returns the minimum value index in Len array that hasn't been visited
  int min = INT_MAX;
  int pos;
  for(int i = 0; i < vertices; i++) {
    if(visited[i] == false && Len[i] <= min) { //smaller and not visited
      min = Len[i];
      pos = i;
    }
  }
  return pos;
}

void AdjList::ShortestPath(int u, int v) { //returns length of shortest path in adjList
  int Len[vertices]; //shortest path to each vertex
  bool visited[vertices]; //keeps track of where we've been
  for(int i = 0; i < vertices; i++) {
    visited[i] = false;
    Len[i] = INT_MAX; //begin with infinity
  }
  Len[u] = 0; //shortest path to itself is 0
  for(int i = 0; i < vertices; i++) { //until we reach our desired vertex
    if(visited[v])
      break;
    int s = MinLen(Len, visited); //find shortest unvisited length
    visited[s] = true;
    for(int j = 0; j < vertices; j++) {
      if(!visited[j] && Len[s] + 1 < Len[j] && adjList[s]->Contains(j) && Len[s] != INT_MAX) //update shortest paths if new shortest found
        Len[j] = Len[s] + 1;
    }
  }
  if(Len[v] != INT_MAX)
    std::cout << "shortest-path: " << Len[v] << std::endl;
  else
    std::cout << "no path between " << u << " and " << v << std::endl;
}

int AdjList::Diameter() {
  int** dist = new int*[vertices];
  for(int i = 0; i < vertices; i++)
    dist[i] = new int[vertices]; //declare it this way to avoid memory leaks
  int max = 0;
  for(int i = 0; i < vertices; i++) {
    for(int j = 0; j < vertices; j++)
      dist[i][j] = INT_MAX; //set all to infinity
    for(int j = 0; j < adjList[i]->Length(); j++)
      dist[i][adjList[i]->Retrieve(j)] = 1; //for each adjacent vertex put a one in the right place
  }
  for(int i = 0; i < vertices; i++)
      dist[i][i] = 0; //0's on the diagonal because distance to oneself is 0
  for(int k = 0; k < vertices; k++) {
    for(int i = 0; i < vertices; i++) {
      for(int j = 0; j < vertices; j++) {
        if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX  && dist[i][j] > dist[i][k] + dist[k][j]) //if shorter intermediary path update dist
          dist[i][j] = dist[i][k] + dist[k][j]; //avoid integer overflow
      }
    }
  }
  for(int i = 0; i < vertices; i++) { //loops through all to find the biggest
    for(int j = 0; j < vertices; j++) {
      if(dist[i][j] > max && dist[i][j] != INT_MAX)
        max = dist[i][j];
    }
  }
  for(int i = 0; i < vertices; i++) //clean up after ourselves
    delete[] dist[i];
  return max;
}

void AdjList::Kruskal() {
  AdjList* tmpList = new AdjList(vertices, vertices - 1); //stores adjList of MST
  for(int i = 0; i < vertices; i++) {
    for(int j = 0; j < adjList[i]->Length(); j++)
      if(tmpList->adjList[adjList[i]->Retrieve(j)]->Length() == 0) { //if destination unvisited
        tmpList->AddEdge(i, adjList[i]->Retrieve(j)); //add edge to MST
        std::cout << i << "--" << adjList[i]->Retrieve(j) << " " << std::endl;
    }
  }
  delete tmpList;
}
