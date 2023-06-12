#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void printMatrix(vector<vector<double>>& matrix) {
	for (auto row : matrix) {
		for (auto element : row) {
			cout << element << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int readInputs(string directory) {
	
	// Read in txt file for 4 ad_matricies

	/*
	1- Adjacency Matrix
	2- Bandwidth Matrix
	3- Delay Matrix
	4- Reliability Matrix
	5- Son matrix skip edebilirsin :)
	*/
	ifstream inFile(directory);
	if (!inFile) {
		cout << "Unable to open input file" << endl;
		return 1;
	}


	int N = 0;
	string line, num;
	vector<vector<double>> edges_mat;
	while (getline(inFile, line)) {
		if (line.empty()) {
			break;
		}
		vector<double> temp;
		edges_mat.push_back(temp);
		istringstream iss2(line);
		do {
			iss2 >> num;
			double x = stod(num);
			edges_mat[N].push_back(x);
		} while (iss2);
		edges_mat[N].pop_back(); // TODO: fix this
		N++;
	}
	printMatrix(edges_mat);

	N = 0;
	vector<vector<double>> bandwidth_mat;
	while (getline(inFile, line)) {
		if (line.empty()) {
			break;
		}
		vector<double> temp;
		bandwidth_mat.push_back(temp);
		istringstream iss2(line);
		do {
			iss2 >> num;
			double x = stod(num);
			bandwidth_mat[N].push_back(x);
		} while (iss2);
		bandwidth_mat[N].pop_back(); // TODO: fix this
		N++;
	}
	printMatrix(bandwidth_mat);

	N = 0;
	vector<vector<double>> delay_mat;
	while (getline(inFile, line)) {
		if (line.empty()) {
			break;
		}
		vector<double> temp;
		delay_mat.push_back(temp);
		istringstream iss2(line);
		do {
			iss2 >> num;
			double x = stod(num);
			delay_mat[N].push_back(x);
		} while (iss2);
		delay_mat[N].pop_back(); // TODO: fix this
		N++;
	}
	printMatrix(delay_mat);

	N = 0;
	vector<vector<double>> reliability_mat;
	while (getline(inFile, line)) {
		if (line.empty()) {
			break;
		}
		vector<double> temp;
		reliability_mat.push_back(temp);
		istringstream iss2(line);
		do {
			iss2 >> num;
			double x = stod(num);
			reliability_mat[N].push_back(x);
		} while (iss2);
		reliability_mat[N].pop_back(); // TODO: fix this
		N++;
	}
	printMatrix(reliability_mat);





}