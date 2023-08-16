// Driver for Multi-weight Disjoint Path finder

#include "Input.h"
#include "transactions.h"
#include "algorithm.h"

using namespace std; 



int main() {
	bool verbose = true;
	int s, t, k, Num_Nodes, Num_trans;
	s = 11;
	t = 2;
	k = 3; // pathlet_nums
	Num_trans = 1000;
	Num_Nodes = 14;
	// Generate Random Transactions
	vector<Transaction> Transactions = create_tranactions(verbose, k, Num_Nodes, Num_trans);

	// Print Generated Transactions
	print_transactions(Transactions);



	
	double min_bandwidth = 10.0; // Minimum bandwidth constraint
	double max_delay = 50.0;    // Maximum delay constraint

	// Call Algorithm
	//find_disjoint_path(Transactions, s, t, min_bandwidth, max_delay);
	find_all_disjoints(Transactions, s, t, min_bandwidth, max_delay);

	//int start = 3;
	//int dest = 10;

	//// everything is 0 indexed
	//start = start - 1;
	//dest = dest - 1; 
	//// Assign these threshold values for min_bandwidth, min_reliability, max_delay 
	//// ASK ABOUT THIS: all 3 parameters assumed to be inclusive (e.g. given minimum bandwidth value is valid for algorithm to use)
	//double min_bandwidth = 3;
	//double min_reliability = 0; //reliability at each edge
	//double max_delay = 999;
	//double overall_reliability = 10;

	//// Directory to input file
	//string directory = "adjacency_14_0_1_2_updated.txt";

	//// Create Graph Object: contains 2d vectors of weights + graph specific threshold values
	//Graph G(directory, start, dest);
	//
	//// Read in Adjacency Matricie 
	//G.readInputs(directory); 

	//// Call algorithm, running values for current bandwidth, reliability and delay
	//G.allDisjointPaths(min_bandwidth, min_reliability, max_delay, overall_reliability);

	//// Create example transactions
	//vector<Transaction> ex_trans = //create_tranactions();

	//// Update Graphs and run algorithm again:
	//G.updateGraph(ex_trans);
	//G.allDisjointPaths(min_bandwidth, min_reliability, max_delay, overall_reliability);
	//
	//// Print and Exit
	//cout << "No more disjoint paths possible" << endl;

	return 0; 
}
