/*
Write a program to eliminate left recursion from the given grammar.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to eliminate left recursion from a single non-terminal
void eliminateLeftRecursion(string nonTerminal, vector<string> productions) {
    vector<string> alpha;  // left recursive part (A → Aα)
    vector<string> beta;   // non-left-recursive part (A → β)

    for (string prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            // Left-recursive production
            alpha.push_back(prod.substr(1));  // remove the leading non-terminal
        } else {
            beta.push_back(prod);
        }
    }

    if (alpha.empty()) {
        // No left recursion
        cout << nonTerminal << " -> ";
        for (int i = 0; i < productions.size(); i++) {
            cout << productions[i];
            if (i != productions.size() - 1)
                cout << " | ";
        }
        cout << endl;
    } else {
        string newNT = nonTerminal + "'";  // new non-terminal A'

        // A → βA'
        cout << nonTerminal << " -> ";
        for (int i = 0; i < beta.size(); i++) {
            cout << beta[i] << newNT;
            if (i != beta.size() - 1)
                cout << " | ";
        }
        cout << endl;

        // A' → αA' | ε
        cout << newNT << " -> ";
        for (int i = 0; i < alpha.size(); i++) {
            cout << alpha[i] << newNT << " | ";
        }
        cout << "#\n";  // epsilon represented as '#'
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    map<string, vector<string>> grammar;
    cout << "Enter productions (example: E->E+T|T):\n";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        string lhs = s.substr(0, s.find("->"));
        string rhs = s.substr(s.find("->") + 2);

        stringstream ss(rhs);
        string prod;
        while (getline(ss, prod, '|')) {
            grammar[lhs].push_back(prod);
        }
    }

    cout << "\nGrammar after eliminating left recursion:\n";
    for (auto &entry : grammar) {
        eliminateLeftRecursion(entry.first, entry.second);
    }

    return 0;
}