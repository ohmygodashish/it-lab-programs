/*
Write a program to construct the LL(1) parsing table for the given grammar.
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> grammar;   // Grammar rules
unordered_map<char, set<char>> FIRST, FOLLOW;  // Input FIRST/FOLLOW sets
map<pair<char, char>, string> parsingTable;    // LL(1) table

// ---------- Build LL(1) Parsing Table ----------
void constructParsingTable() {
    for (auto &entry : grammar) {
        char A = entry.first;
        for (string prod : entry.second) {
            // Compute FIRST(α)
            set<char> firstAlpha;
            bool hasEpsilon = false;

            for (int i = 0; i < prod.size(); i++) {
                char X = prod[i];
                if (!isupper(X)) {
                    firstAlpha.insert(X);
                    break;
                } else {
                    for (char c : FIRST[X]) {
                        if (c == '#') hasEpsilon = true;
                        else firstAlpha.insert(c);
                    }
                    if (FIRST[X].find('#') == FIRST[X].end()) {
                        hasEpsilon = false;
                        break;
                    } else {
                        hasEpsilon = true;
                    }
                }
            }

            // Case 1: For all a in FIRST(α) - {ε}, add M[A,a] = A->α
            for (char a : firstAlpha) {
                if (a != '#') parsingTable[{A, a}] = prod;
            }

            // Case 2: If ε ∈ FIRST(α), add for all b in FOLLOW(A): M[A,b] = A->α
            if (hasEpsilon || prod == "#") {
                for (char b : FOLLOW[A]) {
                    parsingTable[{A, b}] = prod;
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
        string rhs = rule.substr(3); // Skip "A->"

        stringstream ss(rhs);
        string prod;
        while (getline(ss, prod, '|')) {
            grammar[lhs].push_back(prod);
        }
    }

    int f;
    cout << "\nEnter number of FIRST sets: ";
    cin >> f;
    cout << "Enter FIRST sets (e.g., E ( i)\n";
    for (int i = 0; i < f; i++) {
        char nt;
        string temp;
        cin >> nt;
        getline(cin, temp);
        stringstream ss(temp);
        string s;
        while (ss >> s) {
            FIRST[nt].insert(s[0]);
        }
    }

    int fo;
    cout << "\nEnter number of FOLLOW sets: ";
    cin >> fo;
    cout << "Enter FOLLOW sets (e.g., E $ ) )\n";
    for (int i = 0; i < fo; i++) {
        char nt;
        string temp;
        cin >> nt;
        getline(cin, temp);
        stringstream ss(temp);
        string s;
        while (ss >> s) {
            FOLLOW[nt].insert(s[0]);
        }
    }

    constructParsingTable();

    // ---------- Print Parsing Table ----------
    cout << "\nLL(1) Parsing Table:\n";
    cout << left << setw(10) << "NonTerm" << setw(10) << "Input" << "Production\n";
    cout << "---------------------------------\n";

    for (auto &entry : parsingTable) {
        cout << left << setw(10) << entry.first.first
             << setw(10) << entry.first.second
             << entry.first.first << "->" << entry.second << "\n";
    }

    return 0;
}