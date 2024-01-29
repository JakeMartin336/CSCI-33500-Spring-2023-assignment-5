# assignment-5-JakeMartin336
assignment-5-JakeMartin336 created by GitHub Classroom


For Part 1:
This program takes in 2 files. The first file contains the number of vertices, what vertices are connected and the weight of their edges. The second file contains another list of vertices, based upon the first file that was submitted and see if they are adjacent or not. CreateGraphAndTest takes in the two files that are passed, and from the first file, creates and calls the graph.h class to initiate a Graph object. CreateGraphAndTest then goes through the rest of the file, line by line, and creates a graph based upon the file that was passed. CreateGraphAndTest then takes in the second file, and compares it to the graph that was created using the first file. If the vertex is adjacent then it will print that it is connected, and the weight of the edge. The graph.h file consists of a graph class that has a vector of vectors that stores pairs. This nested vector stores each vertex, and the vertices that are connected to it and the weight (as a pair). The graph class also contains a constructor, a method to add edges and a function that returns the weight of the connection between two vertices. 

For Part 2:
This program takes in 2 files. The first file contains the number of vertices, what vertices are connected and the weight of their edges. The second file contains a single start vertex, that the program will use to find the shortest path in the graph to the vertex passed. FindPaths takes in the two files that are passed, and from the first file, creates and calls the graph.h class to initiate a Graph object. FindPaths then goes through the rest of the file, line by line, and creates a graph based upon the file that was passed. FindPaths then takes in the second file and calls the findPaths() method in the Graph object to find the shortest path. Lastly, FindPaths initiates the cost, preVertex, and visited vectors. The graph.h class is further built upon from part 1. Now there is a struct called Vertex, new methods such as findPaths() and dijkstrasAlgorithm, as well as the vectors cost, preVertex, and visited. The dijkstrasAlgorithm() implements Dijkstra's algorithm for finding the shortest path from a starting vertex to all other vertices in a graph. It implements a binary heap to efficiently process vertices based on their current shortest path distance. The findPaths() method firstly calls the dijkstrasAlgorithm() method to calculate the shortest path distances from the start vertex to all other vertices. findPaths() then prints the vertex index followed by a colon and Iterates over the vertices in the path vector and prints the total weight (cost) of the shortest path.
