/*
Write a program to find the FIRST set for the given grammar.
*/

#include <bits/stdc++.h>
using namespace std;	

unordered_map<char, vector<string>> grammar; // Stores grammar rules
unordered_map<char, set<char>> first;        // Stores FIRST sets
unordered_map<char, bool> visited;           // Marks visited non-terminals

void findFirst(char X) {
    // If already computed, skip
    if (visited[X]) return;
    visited[X] = true;

    for (string prod : grammar[X]) { // For each production of X
        for (int i = 0; i < prod.size(); i++) {
            char symbol = prod[i];

            // Case 1: If symbol is terminal or ε (epsilon)
            if (!isupper(symbol)) { 
                first[X].insert(symbol);
                break; // Stop scanning further symbols in this production
            }
            // Case 2: If symbol is non-terminal
            else {
                findFirst(symbol);
                bool hasEpsilon = false;

                // Add FIRST(symbol) - {ε} to FIRST(X)
                for (char c : first[symbol]) {
                    if (c == '#') hasEpsilon = true; // '#' denotes ε
                    else first[X].insert(c);
                }

                // If symbol doesn't produce ε, stop
                if (!hasEpsilon) break;

                // If ε and last symbol, add ε to FIRST(X)
                if (hasEpsilon && i == prod.size() - 1)
                    first[X].insert('#');
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Use # for epsilon (ε)\n";
    cout << "Enter productions (e.g., E->TR | T):\n";

    // Input grammar
    for (int i = 0; i < n; i++) {
        string rule;
        cin >> rule;
        char lhs = rule[0];
        string rhs = rule.substr(3); // skip "A->"

        // Split RHS by '|'
        stringstream ss(rhs);
        string prod;
        while (getline(ss, prod, '|')) {
            grammar[lhs].push_back(prod);
        }
    }

    // Compute FIRST sets for all non-terminals
    for (auto it : grammar) {
        if (!visited[it.first]) findFirst(it.first);
    }

    // Print FIRST sets
    cout << "\nFIRST sets:\n";
    for (auto it : first) {
        cout << "FIRST(" << it.first << ") = { ";
        for (char c : it.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}