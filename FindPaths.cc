//Jacob Martin
#include <iostream>
#include <vector>
#include <string>
#include <fstream> //added
#include <sstream> //added
#include <string> //added

#include "graph.h"
#include "binary_heap.h"

using namespace std;

int pathfindDriver(int argc, char **argv) 
{

  //making sure file 1 is readable
  ifstream graph_file(argv[1]);
  if (!graph_file.is_open()) 
  {
    cout << "Could not open file " << argv[1] << endl;
    return 1;
  }

  int num_vertices;
  graph_file >> num_vertices; //reading the first line
  Graph graph(num_vertices); //setting the number of number of vertices from the file

  string line;
  getline(graph_file, line); // consume newline after reading num_vertices
  while (getline(graph_file, line)) //reading the file line by line
  {
    istringstream iss(line); //put the line from the file to a stringstream
    int vertex;
    iss >> vertex; //reading the vertex with the connected vertexs
    int connected_vertex;
    double weight;
    while (iss >> connected_vertex >> weight) //while the line has more vertex and weights that are connected to the base vertex
      graph.addEdge(vertex,connected_vertex,weight); //store them in the graph that was created
  }

  graph.setShortPath(); //initiating the vector
  graph.setPreVertex(); //initiating the vector
  graph.setVisited(); //initiating the vector

  graph_file.close(); //close the file


  int startVertex = atoi(argv[2]); //reading the second arguement into a string and converting it to an int
  graph.findPaths(startVertex); //calling the findPaths() method using the second file passed
  
  return 0;
}

int main(int argc, char **argv) 
{
  if (argc != 3) 
  {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
    return 0;
  }

  pathfindDriver(argc, argv);

  return 0;
}
