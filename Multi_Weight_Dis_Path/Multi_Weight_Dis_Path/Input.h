#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "transactions.h"

using namespace std;




class Graph {
private:
	string directory;
	int N; // NxN matrix
	int s; // start node
	int t; // end node
	double t_delay; // keep track of delay of end node
	vector<vector<double>> edges;
	vector<vector<double>> bandwidth;
	vector<vector<double>> delay;
	vector<vector<double>> reliability;
	// Assign threshold values for cur_bandwidth, cur_reliability and cur_delay
	double cur_bandwidth;  
	double cur_reliability; 
	double cur_delay;
	

public:
	Graph(string in, int start, int dest);  
	void readInputs(string dir);
	void allDisjointPaths(double min_bandwidth, double min_reliability, double max_delay, double overall_reliability);
	void check_st(double min_bandwidth, double min_reliability, double max_delay, int &counter, double overall_reliability, double &st);
	bool dijkstra(vector<bool>& nodes, const double min_bandwidth, const double min_reliability, const double max_delay, int counter, double overall_reliability);
	void updateGraph(vector<Transaction> &NewTransactions);

	// vector for a list of transactions
	vector<Transaction> Transactions;
};



void printMatrix(vector<vector<double>>& matrix) {
	for (auto row : matrix) {
		for (auto element : row) {
			cout << element << " ";
		}
		cout << endl;
	}
	cout << endl;
}




Graph::Graph(string in_dir, int in_start, int in_dest) : directory{ in_dir }, s{ in_start }, t{ in_dest }, 
N{ 0 }, cur_bandwidth{ -1 }, cur_reliability{ -1 }, cur_delay{ INFINITY } {}


vector<vector<double>> createMat(int &N, ifstream &inFile) {
	N = 0;
	vector<vector<double>> matrix;
	string line, num;
	while (getline(inFile, line)) {
		if (line.empty()) {
			break;
		}
		vector<double> temp;
		matrix.push_back(temp);
		istringstream iss2(line);
		do {
			iss2 >> num;
			double x = stod(num);
			matrix[N].push_back(x);
		} while (iss2);
		matrix[N].pop_back(); 
		N++;
	}
	printMatrix(matrix);

	return matrix;
}

void Graph::readInputs(string dir) {

	// Read in txt file for 4 ad_matricies

	/*
	1- Adjacency Matrix
	2- Bandwidth Matrix
	3- Delay Matrix
	4- Reliability Matrix
	5- Son matrix skip edebilirsin :)
	*/
	ifstream inFile(dir);
	if (!inFile) {
		cout << "Unable to open input file" << endl;
	}

	vector<vector<double>> edges_mat = createMat(N, inFile);
	vector<vector<double>> bandwidth_mat = createMat(N, inFile);
	vector<vector<double>> delay_mat = createMat(N, inFile);
	vector<vector<double>> reliability_mat = createMat(N, inFile);

	edges = edges_mat;
	bandwidth = bandwidth_mat;
	delay = delay_mat;
	reliability = reliability_mat;

}

void printPath(int currentVertex, vector<int> parents, vector<bool>& nodes) {

	if (parents[currentVertex] == -1) {
		return;
	}
	printPath(parents[currentVertex], parents, nodes);
	cout << " --> " << currentVertex + 1;
	nodes[currentVertex] = true;

}

void printSolution(int src, double bdw, double rlb, double delay, vector<int> path, int dest, vector<bool>& nodes, int counter, double cur_reliability, double overall_reliability, double max_delay) {
	if (rlb >= overall_reliability && delay <= max_delay) {
		cout << "This is the disjoint path #" << counter << endl;
		cout << "Minimum bandwidth in path: " << bdw << " Total reliability product in path: " << rlb << " Total delay in path: " << delay << endl;
		cout << "Vertex traversal: " << endl;
		cout << src + 1;
		printPath(dest, path, nodes);
		cout << endl;
	}
}
//not getting past first run through..
bool Graph::dijkstra(vector<bool>& nodes, const double min_bandwidth, const double min_reliability, const double max_delay, int counter, double overall_reliability) { 
vector<double> bw_v(N, -1);
vector<double> delay_v(N, INFINITY);
vector<double> rlb_v(N, -1);
vector<int> path(N);

path[s] = -1;
bw_v[s] = INFINITY;
delay_v[s] = 0;
rlb_v[s] = INFINITY;
vector<bool> sptSet = nodes;

for (int i = 1; i < N; i++) {
	int nearestVertex = -1;
	cur_bandwidth = min_bandwidth;
	cur_delay = max_delay;
	cur_reliability = min_reliability;
	rlb_v[s] = INFINITY;

	for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) {
		if (!sptSet[vertexIndex] && bw_v[vertexIndex] >= cur_bandwidth && delay_v[vertexIndex] < cur_delay && rlb_v[vertexIndex] >= cur_reliability) {
			nearestVertex = vertexIndex;
			cur_bandwidth = bw_v[vertexIndex];
			cur_delay = delay_v[vertexIndex];
			cur_reliability = rlb_v[vertexIndex];

		}
	}
	if (nearestVertex == -1) {
		return false;
	}
	sptSet[nearestVertex] = true;

	for (int j = 0; j < N; j++) {
		double min_bdw = bandwidth[nearestVertex][j];
		double added_dly = delay[nearestVertex][j];
		double new_rlb = reliability[nearestVertex][j];
		if (cur_reliability == INFINITY) {
			cur_reliability = 1;
		}
		if (added_dly > 0 && min_bdw >= bw_v[j] && cur_bandwidth >= bw_v[j] && min_bdw >= min_bandwidth && (cur_delay + added_dly) <= delay_v[j] && (cur_delay + added_dly) <= max_delay && (new_rlb * cur_reliability >= rlb_v[j] || j == s)) {
			path[j] = nearestVertex;
			bw_v[j] = min(min_bdw, cur_bandwidth);
			rlb_v[j] = new_rlb * cur_reliability;
			delay_v[j] = cur_delay + added_dly;

			if (j == t) {
				printSolution(s, bw_v[t], rlb_v[t], delay_v[t], path, t, nodes, counter, cur_reliability, overall_reliability, max_delay);
				return true;
			}
		}
	}
}

return false;
}

void Graph::check_st(double min_bandwidth, double min_reliability, double max_delay, int& counter, double overall_reliability, double& st) {
	if (edges[s][t]) {
		if (bandwidth[s][t] >= min_bandwidth && reliability[s][t] >= min_reliability && delay[s][t] <= max_delay && reliability[s][t] >= overall_reliability) { // direct edge from s to t
			cout << "This is the disjoint path #" << counter++ << endl;
			cout << "Minimum bandwidth in path: " << bandwidth[s][t] << " Total reliability product in path: " << reliability[s][t] << " Total delay in path: " << delay[s][t] << endl;
			cout << "Vertex traversal pathlet: " << endl;
			cout << s + 1 << " --> " << t + 1 << endl;
		}
		st = edges[s][t];
	}
	edges[s][t] = edges[t][s] = 0;
	delay[s][t] = delay[t][s] = 0;
}

void Graph::allDisjointPaths(double min_bandwidth, double min_reliability, double max_delay, double overall_reliability) {
	vector<bool> nodePath(N, false);
	double st = 0;
	t_delay = delay[s][t];
	bool B = true;
	for (int counter = 1; B; counter++) {
		check_st(min_bandwidth, min_reliability, max_delay, counter, overall_reliability, st);
		B = dijkstra(nodePath, min_bandwidth, min_reliability, max_delay, counter, overall_reliability);
		nodePath[t] = false;

	}
	edges[s][t] = edges[t][s] = st;
	delay[s][t] = delay[t][s] = t_delay;
	cout << endl;
	return;
}



//
void Graph::updateGraph(vector<Transaction> &NewTransactions) {
	Transactions = NewTransactions;
	for (auto t : Transactions) {
		vector<int> path;
		string temp = "";
		for (auto c : t.pathletID) {
			if (c == '_') {
				path.push_back(stoi(temp) - 1);
				temp.clear();
			}
			else {
				temp.push_back(c);
			}
		}
		path.push_back(stoi(temp) - 1);
		auto it = next(path.begin(), 1);
		for (auto it2 = path.begin(); it != path.end(); it++, it2++) {
			if (edges[*it][*it2] || edges[*it][*it2]) {
				bandwidth[*it][*it2] = bandwidth[*it2][*it] = t.min_bdw;
				delay[*it][*it2] = delay[*it2][*it] = t.delay;
			}

		}
	}

	printMatrix(bandwidth);
	printMatrix(delay);

	return;
}