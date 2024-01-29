//Jacob Martin
#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <vector> //added
#include <algorithm>//added
#include <iomanip>//added
#include <utility>//added

#include "binary_heap.h"

using namespace std;


struct Vertex
{
    int vertex; // The index of the vertex in the graph
    double shortestPath; // The shortest distance from the starting vertex to the vertex with index `vertex`

    // Constructor that initializes vertex and shortestPath to 0
    Vertex() : vertex(0), shortestPath(0)
    {
    }

    // Constructor that sets vertex and shortestPath to parameters passed
    Vertex(int vert, double dist) : vertex(vert), shortestPath(dist)
    {
    }

    // Overloads the less-than operator to compare two Vertex object's shortestPath variable
    bool operator < (const Vertex& comp) const 
    {
        return this->shortestPath < comp.shortestPath;
    }

    // Overloads the greater-than operator to compare two Vertex object's shortestPath variable
    bool operator > (const Vertex& comp) const
    {
        return this->shortestPath > comp.shortestPath;
    }
};


class Graph
{
public:
    Graph(int numVertices) : adjList(numVertices+1) , totalVertices(numVertices) //constructor that creates the vector of the size provided
    {
        adjList[0].push_back(make_pair(0, 0.0));
    }

    void addEdge(int src, int dest, double weight) //add the connected vertex to the list
    {
        adjList[src].push_back(make_pair(dest, weight)); //goes to the index of the vector that stores the base vertex, then adds the connected vertex and its weight to the vertex's vector as a pair
    }

    const vector<pair<int, double>>& getAdjList(int vertex) const //returns the vertex that is in that index of the vector
    {
        return adjList[vertex]; //returning the index that corresponds to the vertex
    }

    bool isAdjacent(int src, int dest) const //function that checks if two vertex are connected
    {
        vector<pair<int, double>> temp = adjList[src]; //storing the base vertex's vector as a temp vector
        for (const auto& pair : temp) //cycling through the vector that was stored at the index
            if(pair.first == dest) //if the vertex is stored in the base vertex's vector
                return true; //return true
        return false; //if looped through the entire base vertex's vector and the vertex isnt present, return false
    }

    double getWeight(int src, int dest) const //function that returns the weight of the edge between two vertex
    {
        vector<pair<int, double>> temp = adjList[src]; //storing the base vertex's vector as a temp vector
        for (const auto& pair : temp) //cycling through the vector that was stored at the index
            if(pair.first == dest) //if the vertex is stored in the base vertex's vector
                return pair.second; //return the weight of the edge that connects the vertex
        return 0.0; //if looped through the entire base vertex's vector and the vertex isnt present, return 0.0
    }

    // void printGraph() const //helper function for debugging that prints the entire graph's adjacency list
    // {
    //     int i = 1;
    //     for (const auto& pair : adjList)
    //     {
    //         std::vector<std::pair<int, double>> temp = pair;
    //         for (const auto& pair : temp)
    //             std::cout  << i << " : "<< pair.first << " " << pair.second << "\n";
    //         i += 1;
    //     }
    // }

    void dijkstrasAlgorithm(int startingVertex)
    {
        BinaryHeap<Vertex> vertexList; //creating the BinaryHash object, that is filled with the struct Vertex objects
        int currV, nextV; //variables to store the current vertex, and the next vertex
        double nextC, currD; //variables to store the cost of the next vertex, and the current shortest path distance

        visited[startingVertex] = true; //marking that we have been to the starting vertex already
        cost[startingVertex] = 0; //add 0 to the vector since there is no weight going to itself
        preVertex[startingVertex] = startingVertex; //mark where the vertex is to keep track

        vertexList.insert(Vertex(startingVertex, 0.0)); //add the startVertex to the BinaryHeap, as a new Vertex Object

        while(!vertexList.isEmpty()) //loop until vertexList is empty
        {
            currV = vertexList.findMin().vertex; //get the vertex index with the minimum shortest path distance from vertexList
            currD = vertexList.findMin().shortestPath; //get the shortest path distance from VertexList
            vertexList.deleteMin(); //remove the minimum vertex 
            visited[currV] = true; //mark the current vertex as visited

            for(auto nextVertex: adjList[currV]) //cycle through the adjacent vertices of the current vertex 
            {
                nextV = nextVertex.first; //get the next vertex index
                nextC = nextVertex.second + currD; //the cost to reach the next vertex index

                if( visited[nextV]) //if the vertex has already been visited, skip
                    continue;
                if(cost[nextV] == -1 || (cost[nextV] > nextC)) //if the vertex hasnt been visited or if the cost to reach the next vertex is greater than the updated cost, loop
                {
                    cost[nextV] =  nextC; //set the cost to reach the next vertex
                    preVertex[nextV] = currV; //set the previous of the next vertex as the current vertex
                    vertexList.insert(Vertex(nextV, nextC)); //insert the next vertex into vertexList with the updated shortest path distance
                }
            }
        }
    }
    

    void findPaths(int startVertex) //function that finds the shortest paths from the startVertex to all other vertices
    {
        dijkstrasAlgorithm(startVertex); //calling the Dijkstra’s Algorithm method using the parameter passed

        for (int i = 1; i <= totalVertices; i++) //cycling through the vector of double, which stores the weight of the edges connected
        {
            if (cost[i] == -1) //if the vector index contains -1, then there is no possible path
            {
                cout << i << ": not_possible" << endl; //print in the format given
                continue;
            }

            vector<int> path; //creating a new vector that stores the path as a sequence of vertices
            int tempIndex = i; 
            path.push_back(tempIndex); //since the index did not contain -1, there is a possible path, so we store it in the new vector

            while (tempIndex != startVertex) //when it reaches the startVertex, then we have found the complete path
            {
                tempIndex = preVertex[tempIndex]; //getting the value that is stored at the index
                path.push_back(tempIndex); //putitng the value in the vector
            }

            reverse(path.begin(), path.end()); //inorder to read the path correctly, we must reverse it

            cout << i << ": "; //printing in the format given by Prof.
            for (int j = 0; j < path.size(); j++) //cycling through the vector that contains the vertex's that make up the path and printing them out
            {
                //printing in the format given by Prof. 
                cout << path[j];
                if (j < path.size() - 1)
                    cout << " ";
            }
            cout << " cost: " << fixed << setprecision(1) << cost[i] << endl; //printing the total weight of the path
        }
    }


    void setShortPath()
    {
       cost = vector<double>(totalVertices + 1, -1); //setting the size and what is contained at each index of the vector
    }

    void setPreVertex()
    {
        preVertex = vector<int> (totalVertices + 1, -1); //setting the size and what is contained at each index of the vector
    }

    void setVisited()
    {
        visited = vector<bool>(totalVertices + 1, false); //setting the size and what is contained at each index of the vector
    }


private:
    vector<vector<pair<int, double>>> adjList; //a vector of vector's, that stores pairs at each index of the nested vector. Each index of the base vector represents a vertex.
    int totalVertices; //number of vertices in the graph
    
    vector<double> cost; //vector that stores the weight of the shortest path
    vector<int> preVertex; //vector that keeps track of the order of the vertices
    vector<bool> visited; //vector that keeps track if we've already visitied this vertex


};


#endif
