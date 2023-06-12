// Driver for Multi-weight Disjoint Path finder

#include "Input.h"

using namespace std; 

int main() {

	int start = 3;
	int dest = 10;

	// everything is 0 indexed
	start = start - 1;
	dest = dest - 1; 
	// Assign these threshold values for min_bandwidth, min_reliability, max_delay 
	// ASK ABOUT THIS: all 3 parameters assumed to be inclusive (e.g. given minimum bandwidth value is valid for algorithm to use)
	double min_bandwidth = 0;
	double min_reliability = 0; //reliability at each edge
	double max_delay = 25;
	double overall_reliability = 60;

	// Read in Adjacency Matricies: 
	string directory = "adjacency_14_0_1_2_updated.txt";
	//cout << directory << endl;
	Graph G(directory, start, dest);
	G.readInputs(directory); //struct containing 2d vectors + graph specific threshold values
	G.allDisjointPaths(min_bandwidth, min_reliability, max_delay, overall_reliability);

	// Call algorithm, running values for current bandwidth, reliability and delay
	cout << "No more disjoint paths possible" << endl;

	return 0; 
}
