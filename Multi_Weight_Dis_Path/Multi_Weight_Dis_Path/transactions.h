#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;




// Transaction class:
class Transaction {
public:
	string ID;
	int signature;	string ASN;
	vector<char> pathletID;
	int ingressNode;
	int egressNode;
	double min_bdw;
	double delay;
	bool used;

	// Default constructor
	Transaction()
		: used(false), ID("0"), signature(0), ASN(""), pathletID(vector<char>()), ingressNode(-1), egressNode(-1), min_bdw(INFINITY), delay(0) {}

	Transaction(string ID_in, int sig_in, string ASN_in, vector<char> pathletID_in, int ingressNode_in = -1, int egressNode_in = -1, double min_bdw_in = INFINITY, double dly_in = 0)
		: used(false), ID(ID_in), signature(sig_in), ASN(ASN_in), pathletID(pathletID_in), ingressNode(ingressNode_in), egressNode(egressNode_in), min_bdw(min_bdw_in), delay(dly_in) {}

	bool operator==(const Transaction& other) const {
		return ID == other.ID && signature == other.signature && ASN == other.ASN &&
			pathletID == other.pathletID && ingressNode == other.ingressNode &&
			egressNode == other.egressNode && min_bdw == other.min_bdw && delay == other.delay;
	}

};

int randomNum(int low, int up) {
	random_device rd;
	mt19937 gen(rd());

	// Create a uniform distribution from the lowerBound to the upperBound (inclusive)
	uniform_int_distribution<int> dis(low, up);

	return dis(gen);
}

// Generate a single Transaction based on parameters below
Transaction generateTransaction(int id, int max_nodes) {
	string ID = "AS2_" + to_string(id + 1);
	int Sig = randomNum(50000, 999999);
	string ASN = "AS2";

	int Ing_N, Eng_N, bdw, dly;	
	do {
		Ing_N = randomNum(0, max_nodes);
		Eng_N = randomNum(0, max_nodes);
	} while (Ing_N == Eng_N); // Make sure Ing_N != Eng_N

	string pathlet_string = "R" + to_string(Ing_N) + "_" + "R" + to_string(Eng_N) + "_" + to_string(1);
	vector<char> pathlet(pathlet_string.begin(), pathlet_string.end());

	bdw = randomNum(0, 20);
	dly = randomNum(0, 20);


	Transaction t(ID, Sig, ASN, pathlet, Ing_N, Eng_N, bdw, dly);

	return t; 
}

vector<Transaction>::iterator findTransactionByPathletID(vector<Transaction>& Ts, const vector<char>& pathletID) {
	return find_if(Ts.begin(), Ts.end(), [pathletID](const Transaction& transaction) {
		return transaction.pathletID == pathletID;
		});
}

// Function to Generate Random Transactions
vector<Transaction> create_tranactions(bool v, int k, int max_nodes, int num_trans) { // 0 indexed s and t 
	vector<Transaction> Ts;
	Transaction temp;
	for (int i = 0; i < num_trans; i++) {
		temp  = generateTransaction(i + 1, max_nodes - 1);
		vector<char> target_pathletID = temp.pathletID;
		auto it = findTransactionByPathletID(Ts, target_pathletID);
		if (it == Ts.end()) {
			Ts.push_back(temp);
			// sort
			sort(Ts.begin(), Ts.end(), [](const Transaction& a, const Transaction& b) {
				return a.pathletID < b.pathletID;
				});
		}
		else {
			bool found = false;
			for (int j = 2; j <= k; j++) {
				target_pathletID.back() = '0' + j;
				auto it2 = findTransactionByPathletID(Ts, target_pathletID);
				if (it2 == Ts.end()) { //pathletID_j DNE
					temp.pathletID = target_pathletID; 
					Ts.push_back(temp);
					// sort
					sort(Ts.begin(), Ts.end(), [](const Transaction& a, const Transaction& b) {
						return a.pathletID < b.pathletID;
						});
					found = true;
					break;
				}
			}
			if (!found) {
				int pid = randomNum(1, k);
				char c = '0' + pid;
				temp.pathletID.back() = c;
				advance(it, pid - 1);
				*it = temp; // replace transaction with pathletID ending in pid num
			}
		}		
	}

	return Ts;
}


void print_transactions(vector<Transaction>& T) {
	for (auto ele : T) {
		cout << "Transaction "; 
		cout << ele.ID << ", " << ele.signature << ", " << ele.ASN << ", ";
		for (auto e : ele.pathletID) {
			cout << e;
		}
		cout << ", " << ele.ingressNode << ", " << ele.egressNode << ", " << ele.min_bdw << ", " << ele.delay << endl;
	}
	cout << T.size() << endl;
	cout << endl;

	return;

}