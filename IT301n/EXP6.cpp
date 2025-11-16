/*
Write a program to perform left factoring on the given grammar.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to find common prefix among all productions of a non-terminal
string commonPrefix(vector<string> &productions) {
    if (productions.empty()) return "";
    string prefix = productions[0];
    for (int i = 1; i < productions.size(); i++) {
        string temp = "";
        for (int j = 0; j < min(prefix.size(), productions[i].size()); j++) {
            if (prefix[j] == productions[i][j])
                temp += prefix[j];
            else
                break;
        }
        prefix = temp;
    }
    return prefix;
}

// Function to perform left factoring on the grammar
void leftFactor(map<string, vector<string>> &grammar) {
    bool changed = true;
    while (changed) {
        changed = false;
        map<string, vector<string>> newGrammar;

        for (auto &entry : grammar) {
            string nonTerminal = entry.first;
            vector<string> prods = entry.second;

            // Group productions by their first character
            unordered_map<char, vector<string>> groups;
            for (string p : prods)
                groups[p[0]].push_back(p);

            bool factored = false;

            for (auto &g : groups) {
                if (g.second.size() > 1) {
                    // Find common prefix
                    string prefix = commonPrefix(g.second);
                    if (prefix.size() > 0) {
                        factored = true;
                        changed = true;

                        string newNT = nonTerminal + "'"; // new non-terminal
                        vector<string> newNTProds;

                        for (string prod : g.second) {
                            string suffix = prod.substr(prefix.size());
                            if (suffix == "") suffix = "#"; // epsilon
                            newNTProds.push_back(suffix);
                        }

                        // Replace old group with the factored version
                        newGrammar[nonTerminal].push_back(prefix + newNT);
                        newGrammar[newNT] = newNTProds;
                    } else {
                        newGrammar[nonTerminal].push_back(g.second[0]);
                    }
                } else {
                    newGrammar[nonTerminal].push_back(g.second[0]);
                }
            }

            if (!factored) {
                // If no factoring occurred, keep productions as-is
                if (newGrammar.find(nonTerminal) == newGrammar.end())
                    newGrammar[nonTerminal] = prods;
            }
        }

        grammar = newGrammar;
    }
}

// Display grammar neatly
void printGrammar(const map<string, vector<string>> &grammar) {
    cout << "\nLeft Factored Grammar:\n";
    for (auto &entry : grammar) {
        cout << entry.first << " -> ";
        for (int i = 0; i < entry.second.size(); i++) {
            cout << entry.second[i];
            if (i != entry.second.size() - 1)
                cout << " | ";
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<string>> grammar;
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions (example: E->iEtS|iEtSeS|a):\n";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        string lhs = s.substr(0, s.find("->"));
        string rhs = s.substr(s.find("->") + 2);

        stringstream ss(rhs);
        string prod;
        while (getline(ss, prod, '|'))
            grammar[lhs].push_back(prod);
    }

    leftFactor(grammar);
    printGrammar(grammar);
    return 0;
}