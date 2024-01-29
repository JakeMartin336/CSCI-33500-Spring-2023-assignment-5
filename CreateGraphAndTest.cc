//Jacob Martin
#include <iostream>
#include <vector>
#include <string>
#include <fstream> //added
#include <sstream> //added
#include <string> //added

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) 
{
  //making sure file 1 is readable
  ifstream graph_file(argv[1]);
  if (!graph_file.is_open()) 
  {
    cout << "Could not open file " << argv[1] << endl;
    return 1;
  }
  //making sure file 2 is readable
  ifstream query_file(argv[2]);
  if (!query_file.is_open()) 
  {
    cout << "Could not open file " << argv[2] << endl;
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

  graph_file.close(); //close the file

  //graph.printGraph();

  // read adjacency queries from file
  int u, v;
  while (query_file >> u >> v) //reading the vertex that on that line in the file
  {
    if (graph.isAdjacent(u, v)) //calling the function that can tell if the two vertex are connected
      cout << u << " " << v << ": connected " << graph.getWeight(u, v) << endl; //if they are connected then print it out with the weight of the edge
    else
      cout << u << " " << v << ": not_connected" << endl; //if not connected then print that
  }
  query_file.close(); //close the file


  return 0;
}

int main(int argc, char **argv) 
{
  if (argc != 3) 
  {
    cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
    return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
