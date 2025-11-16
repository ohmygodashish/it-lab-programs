/*
Write a program to find the FOLLOW set for the given grammar.
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> grammar;   // Grammar rules
unordered_map<char, set<char>> FIRST, FOLLOW;  // Given FIRST sets and computed FOLLOW sets
char startSymbol;

// ---------- Helper: FIRST(α) ----------
set<char> findFirstOfString(string str) {
    set<char> result;
    bool allHaveEpsilon = true;

    for (char symbol : str) {
        if (!isupper(symbol)) {
            result.insert(symbol);
            allHaveEpsilon = false;
            break;
        }
        for (char c : FIRST[symbol]) {
            if (c != '#') result.insert(c);
        }
        if (FIRST[symbol].find('#') == FIRST[symbol].end()) {
            allHaveEpsilon = false;
            break;
        }
    }

    if (allHaveEpsilon)
        result.insert('#');

    return result;
}

// ---------- Compute FOLLOW sets ----------
void computeFollow() {
    FOLLOW[startSymbol].insert('$'); // Start symbol gets $

    bool changed = true;
    while (changed) {
        changed = false;

        for (auto &entry : grammar) {
            char A = entry.first;
            for (string prod : entry.second) {
                for (int i = 0; i < prod.size(); i++) {
                    char B = prod[i];
                    if (isupper(B)) {
                        set<char> temp;

                        // Case 1: There are symbols after B
                        if (i + 1 < prod.size()) {
                            string beta = prod.substr(i + 1);
                            temp = findFirstOfString(beta);

                            // Add FIRST(beta) - {ε}
                            for (char c : temp) {
                                if (c != '#')
                                    if (FOLLOW[B].insert(c).second)
                                        changed = true;
                            }

                            // If FIRST(beta) contains ε, add FOLLOW(A)
                            if (temp.find('#') != temp.end()) {
                                for (char c : FOLLOW[A]) {
                                    if (FOLLOW[B].insert(c).second)
                                        changed = true;
                                }
                            }
                        }
                        // Case 2: B is at end → add FOLLOW(A)
                        else {
                            for (char c : FOLLOW[A]) {
                                if (FOLLOW[B].insert(c).second)
                                    changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

// ---------- MAIN ----------
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Use # for epsilon (ε)\n";
    cout << "Enter productions (e.g., E->TR|T):\n";

    for (int i = 0; i < n; i++) {
        string rule;
        cin >> rule;
        char lhs = rule[0];
        if (i == 0) startSymbol = lhs;
        string rhs = rule.substr(3); // Skip "A->"

        stringstream ss(rhs);
        string prod;
        while (getline(ss, prod, '|')) {
            grammar[lhs].push_back(prod);
        }
    }

    int f;
    cout << "\nEnter number of FIRST sets you know: ";
    cin >> f;
    cout << "Enter them in format: NonTerminal symbols (no spaces)\n";
    cout << "Example: E ( i\nMeans FIRST(E) = { ( , i }\n";
    for (int i = 0; i < f; i++) {
        char nt;
        string s;
        cin >> nt;
        string temp;
        getline(cin, temp);
        stringstream ss(temp);
        while (ss >> s) {
            FIRST[nt].insert(s[0]);
        }
    }

    computeFollow();

    cout << "\nFOLLOW sets:\n";
    for (auto &it : FOLLOW) {
        cout << "FOLLOW(" << it.first << ") = { ";
        for (char c : it.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}