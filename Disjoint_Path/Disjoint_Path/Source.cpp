//Dijkstra's alg and complementary disjoint path alg's

#include <cstdio>
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], vector<bool> sptSet)
{

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

//// A utility function to print the constructed distance
//// array
//void printSolution(int dist[])
//{
//	cout << "Vertex \t Distance from Source" << endl;
//	for (int i = 0; i < V; i++)
//		cout << i << " \t\t\t\t" << dist[i] << endl;
//}
//
//void printPath2(vector<int>& path, int dist[], int src, int dest) {
//	cout << "Distance from Source: " << dist[path.back()] << "Vertex path from source to destination : " << endl;
//	cout << src << " --> ";
//	for (int i = 0; i < path.size(); i++) {
//		cout << path[i] << " --> ";
//	}
//	cout << dest << endl;
//}

void printPath(int currentVertex, vector<int> parents, vector<bool> & nodes)
{
	// Base case : Source node has
	// been processed
	if (parents[currentVertex] == -1) {
		return;
	}
	printPath(parents[currentVertex], parents, nodes);
	cout << " --> " << currentVertex;
	nodes[currentVertex] = true;

}

// A utility function to print
// the constructed distances
// array and shortest paths
void printSolution(int src, vector<int> distances, vector<int> path, int dest, vector<bool>& nodes, int counter)
{
	cout << "This is the " << counter << " shortest disjoint path." << endl;
	cout << "Distance from Source to Destination is " << distances[dest] << endl;
	cout << "Vertex traversal: " << endl;
	cout << src;
	printPath(dest, path, nodes);
	cout << endl;
	
	//for printing out all of traversals: 
	/*
    int nVertices = distances.size();
	for (int i = 0; i < nVertices; i++) {
		if (i != src) {
			cout << "\n" << src << " -> " << i << " \t\t " << distances[i] << "\t\t";
			printPath(i, path);
		}
	}*/
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
bool dijkstra(int graph[V][V], int src, int dest, vector<bool> &nodes, int counter)
{
	vector<int> dist(V, INT_MAX);
	vector<int> path(V);
	path[src] = -1; //starting node

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	vector<bool> sptSet = nodes;

	for (int i = 1; i < V; i++) {

		// Pick the minimum distance vertex
		// from the set of vertices not yet
		// processed. nearestVertex is
		// always equal to startNode in
		// first iteration.
		int nearestVertex = -1;
		int shortestDistance = INT_MAX;
		for (int vertexIndex = 0; vertexIndex < V;
			vertexIndex++) {
			if (!sptSet[vertexIndex] && dist[vertexIndex] < shortestDistance) {
				nearestVertex = vertexIndex;
				shortestDistance = dist[vertexIndex];
			}
		}
		// Mark the picked vertex as
		// processed
		if (nearestVertex == -1) {
			return false;
		}
		sptSet[nearestVertex] = true;

		// Update dist value of the
		// adjacent vertices of the
		// picked vertex.
		for (int i = 0; i < V; i++) {
			int addedDist = graph[nearestVertex][i];

			if (addedDist > 0 && ((shortestDistance + addedDist) < dist[i])) {
				path[i] = nearestVertex;
				dist[i] = shortestDistance + addedDist;
				if (i == dest) {
					printSolution(src, dist, path, dest, nodes, counter);
					return true;
				}
			}
		}
	}	

	return false;

	//// Find shortest path for all vertices
	//for (int count = 0; count < V - 1; count++) {
	//	// Pick the minimum distance vertex from the set of
	//	// vertices not yet processed. u is always equal to
	//	// src in the first iteration.
	//	int u = minDistance(dist, sptSet);

	//	// Mark the picked vertex as processed
	//	sptSet[u] = true;

	//	// Update dist value of the adjacent vertices of the
	//	// picked vertex.
	//	for (int v = 0; v < V; v++)

	//		// Update dist[v] only if is not in sptSet,
	//		// there is an edge from u to v, and total
	//		// weight of path from src to v through u is
	//		// smaller than current value of dist[v]
	//		if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
	//			dist[v] = dist[u] + graph[u][v];
	//			if (u != src && u != dest) {
	//				path.push_back(u);
	//				nodes[u] = true;
	//			}
	//			if (v == dest) { //dest has been reached 
	//				printPath(path, dist, src, dest);
	//				return true;
	//			}
	//		}
	//}
	//return false;

}

void allDisjointPaths(int graph[V][V], int s, int t) { //inputs: graph, start node, end node  

	vector<bool> nodePath(V, false); // nodePath[i] == true if node i has been used in a previous shortest path
	bool B = true;
	int counter = 1; 
	while (B) {
		if (graph[s][t] != 0) {
			cout << "This is the " << counter++ << " shortest disjoint path." << endl;
			cout << "Distance from Source to Destination is " << graph[s][t] << endl;
			cout << "Vertex traversal: " << endl;
			cout << s << " --> " << t << endl;
			graph[s][t] = 0;
			graph[t][s] = 0;
		}
		B = dijkstra(graph, s, t, nodePath, counter++);
		nodePath[t] = false;
	}
	cout << "all done, no more disjoint paths possible" << endl;
	/*bool te = dijkstra(graph, s, t, nodePath);
	nodePath[s] = false;
	nodePath[t] = false; 
	te = dijkstra(graph, s, t, nodePath);
	te = false;*/

	//int edges[V][V]; //2d matrix where edges[i][j] != 0 indicates an edge exists between i and j

	//for (int i = 0; i < V; i++) {
	//	for (int j = 0; j < V; j++) {
	//		edges[i][j] = graph[i][j]; //preform deep copy onto edges
	//	}
	//}
	//
	//int outdist[V]; 
	//bool nodePath[V]; // nodePath[i] == true if node i is used in this shortest path 


	return;
}

// driver's code
int main()
{
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	allDisjointPaths(graph, 8, 2);

	return 0;
}

// This code is contributed by shivanisinghss2110
