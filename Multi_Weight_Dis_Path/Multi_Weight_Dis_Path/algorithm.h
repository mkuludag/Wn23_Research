#pragma once



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

#include "transactions.h"

using namespace std;


// Print Found path Not Needed
void print_path() {


    return;
}



void dfs(vector<Transaction>& T, vector<int>& path, vector<string>& used_transactions, double& min_bdw_in_path, double& total_delay_in_path, int node, int t, double min_bdw, double max_delay) {
    if (node == t || total_delay_in_path > max_delay) {
        return;
    }

    // Sort transactions based on egressNode (use fewer transactions first)
    /*sort(T.begin(), T.end(), [](const Transaction& a, const Transaction& b) {
        return a.egressNode < b.egressNode;
        });*/

    for (int i = 0; i < T.size(); ++i) {
        if (!T[i].used && T[i].ingressNode == node && T[i].min_bdw >= min_bdw && T[i].delay <= max_delay - total_delay_in_path) {
            path.push_back(T[i].egressNode); // Push the egressNode onto the path
            used_transactions.push_back(T[i].ID); // Store the ID of used transaction

            double prev_min_bdw = min_bdw_in_path;
            double prev_total_delay = total_delay_in_path;

            min_bdw_in_path = min(min_bdw_in_path, T[i].min_bdw); // Update minimum bandwidth in path
            total_delay_in_path += T[i].delay; // Update total delay in path
            T[i].used = true; // Mark transaction as used

            dfs(T, path, used_transactions, min_bdw_in_path, total_delay_in_path, T[i].egressNode, t, min_bdw, max_delay);

            if (path.back() == t) {
                return; // Terminate the DFS early if the destination is reached
            }
            else {
                path.pop_back(); // Backtrack
                used_transactions.pop_back(); // Remove the last used transaction
                T[i].used = false; // Reset the used flag
                min_bdw_in_path = prev_min_bdw; // Revert min_bdw_in_path
                total_delay_in_path = prev_total_delay; // Revert total_delay_in_path
            }
        }
    }
}




// Function to find best disjoint path and remove used transactions
bool find_disjoint_path(vector<Transaction>& T, int s, int t, double max_bdw, double max_delay, int count) {
    vector<int> path;
    vector<string> used_transactions;
    double min_bdw_in_path = numeric_limits<double>::max();
    double total_delay_in_path = 0.0;

    dfs(T, path, used_transactions, min_bdw_in_path, total_delay_in_path, s, t, max_bdw, max_delay);

    if (!path.empty() && path.back() == t && total_delay_in_path <= max_delay) {
        cout << "Disjoint path number " << count << " found:" << endl;
        cout << "Path from " << s << " to " << t << ":" << endl;
        cout << s << " -> ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << " (" << used_transactions[i] << ")";
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;

        cout << "Minimum Bandwidth in Path: " << min_bdw_in_path << endl;
        cout << "Total Delay in Path: " << total_delay_in_path << endl;

        // Remove used transactions from the vector
        T.erase(remove_if(T.begin(), T.end(), [](const Transaction& t) { return t.used; }), T.end());

        return true;
    }
    else {
        cout << "No disjoint paths found." << endl;
        return false;
    }
}


// Finds all possible Disjoint paths
void find_all_disjoints(vector<Transaction>& T, int source, int destination, double min_bdw, double max_delay) {
    bool pathFound = true;
    int count = 1;

    while (pathFound) {
        pathFound = find_disjoint_path(T, source, destination, min_bdw, max_delay, count);
    }
}
