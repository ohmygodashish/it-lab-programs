/*
Write a program to parse the string id = id+id generating a sequence-of-moves 
table based on the LL(1) parsing table.
*/

#include <bits/stdc++.h>
using namespace std;

// LL(1) parsing table for the given grammar
map<pair<string, string>, string> table;

// Function to initialize LL(1) parsing table
void initParsingTable() {
    // Grammar:
    // E -> T R
    // R -> + T R | #
    // T -> F Y
    // Y -> * F Y | #
    // F -> ( E ) | id

    table[{"E", "id"}] = "T R";
    table[{"E", "("}]  = "T R";

    table[{"R", "+"}]  = "+ T R";
    table[{"R", ")"}]  = "#";
    table[{"R", "$"}]  = "#";

    table[{"T", "id"}] = "F Y";
    table[{"T", "("}]  = "F Y";

    table[{"Y", "*"}]  = "* F Y";
    table[{"Y", "+"}]  = "#";
    table[{"Y", ")"}]  = "#";
    table[{"Y", "$"}]  = "#";

    table[{"F", "id"}] = "id";
    table[{"F", "("}]  = "( E )";
}

// ---------- Utility Functions ----------
bool isTerminal(const string &x) {
    return !(x == "E" || x == "R" || x == "T" || x == "Y" || x == "F");
}

// ---------- Main Parsing Simulation ----------
void parseString(const string &input) {
    stack<string> st;
    st.push("$");
    st.push("E");

    int ip = 0;
    string remaining = input;

    cout << left << setw(25) << "STACK" 
         << setw(25) << "INPUT"
         << "ACTION\n";
    cout << string(65, '-') << "\n";

    while (!st.empty()) {
        string top = st.top();
        string cur(1, remaining[ip]);

        // For "id", handle multi-character token
        if (remaining.substr(ip, 2) == "id")
            cur = "id";

        cout << setw(25) << top
             << setw(25) << remaining.substr(ip);

        // Case 1: Match terminal
        if (top == cur) {
            cout << "Match " << cur << "\n";
            st.pop();
            if (cur == "id") ip += 2;
            else ip++;
        }

        // Case 2: Non-terminal
        else if (!isTerminal(top)) {
            auto rule = table.find({top, cur});
            if (rule == table.end()) {
                cout << "Error: No rule for (" << top << ", " << cur << ")\n";
                return;
            }

            string production = rule->second;
            cout << top << " -> " << production << "\n";
            st.pop();

            // Push RHS of production in reverse (if not epsilon)
            if (production != "#") {
                vector<string> symbols;
                stringstream ss(production);
                string sym;
                while (ss >> sym)
                    symbols.push_back(sym);
                for (int i = symbols.size() - 1; i >= 0; i--)
                    st.push(symbols[i]);
            }
        }

        // Case 3: Mismatch (terminal on stack ≠ input symbol)
        else {
            cout << "Error: Unexpected symbol '" << cur << "'\n";
            return;
        }

        if (top == "$" && cur == "$") {
            cout << "String accepted.\n";
            return;
        }
    }
}

int main() {
    initParsingTable();

    string input;
    cout << "Enter input string (use 'id' for identifiers, end with $): ";
    cin >> input;

    cout << "\nLL(1) Parsing Simulation:\n\n";
    parseString(input);

    return 0;
}