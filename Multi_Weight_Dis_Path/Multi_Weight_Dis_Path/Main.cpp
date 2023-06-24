// Driver for Multi-weight Disjoint Path finder

#include "Input.h"

using namespace std; 

vector<Transaction> create_tranactions() {
	vector<Transaction> Ts;

	//			   ID	Sig	   ASN		PathetID    Ing_N  Egr_N  bdw  dly
	Transaction t1(1, 93483, "ASN2", { '5', '_', '6', '_', '7' });
	Transaction t2(2, 23452, "ASN2", { '5', '_', '7', '_', '2' }, 10, 20, 8, 20);
	Transaction t3(3, 90234, "ASN2", { '1', '0', '_', '1'}, 30, 40, 15.0, 99);

	Ts.push_back(t1);
	Ts.push_back(t2);
	Ts.push_back(t3);

	return Ts;
}

int main() {

	int start = 3;
	int dest = 10;

	// everything is 0 indexed
	start = start - 1;
	dest = dest - 1; 
	// Assign these threshold values for min_bandwidth, min_reliability, max_delay 
	// ASK ABOUT THIS: all 3 parameters assumed to be inclusive (e.g. given minimum bandwidth value is valid for algorithm to use)
	double min_bandwidth = 3;
	double min_reliability = 0; //reliability at each edge
	double max_delay = 999;
	double overall_reliability = 10;

	// Directory to input file
	string directory = "adjacency_14_0_1_2_updated.txt";

	// Create Graph Object: contains 2d vectors of weights + graph specific threshold values
	Graph G(directory, start, dest);
	
	// Read in Adjacency Matricie 
	G.readInputs(directory); 

	// Call algorithm, running values for current bandwidth, reliability and delay
	G.allDisjointPaths(min_bandwidth, min_reliability, max_delay, overall_reliability);

	// Create example transactions
	vector<Transaction> ex_trans = create_tranactions();

	// Update Graphs and run algorithm again:
	G.updateGraph(ex_trans);
	G.allDisjointPaths(min_bandwidth, min_reliability, max_delay, overall_reliability);
	
	cout << "No more disjoint paths possible" << endl;

	return 0; 
}
