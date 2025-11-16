/*
Implement NFAs to recognize variables and numbers in lexical analysis.
*/

#include <bits/stdc++.h>
using namespace std;

// ----------------------------
// NFA to recognize identifiers
// ----------------------------
bool identifierNFA(const string &word) {
    int state = 0;

    for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        switch (state) {
            case 0:
                if (isalpha(ch) || ch == '_')
                    state = 1; // valid start
                else
                    return false;
                break;

            case 1:
                if (isalnum(ch) || ch == '_')
                    state = 1; // stay in identifier
                else
                    return false;
                break;

            default:
                return false;
        }
    }

    return (state == 1); // final accepting state
}

// ----------------------------
// NFA to recognize numbers
// ----------------------------
bool numberNFA(const string &word) {
    int state = 0;

    for (int i = 0; i < word.size(); i++) {
        char ch = word[i];

        switch (state) {
            case 0:
                if (isdigit(ch))
                    state = 1; // integer part
                else
                    return false;
                break;

            case 1:
                if (isdigit(ch))
                    state = 1; // continue integer
                else if (ch == '.')
                    state = 2; // possible float
                else
                    return false;
                break;

            case 2:
                if (isdigit(ch))
                    state = 3; // fractional part begins
                else
                    return false;
                break;

            case 3:
                if (isdigit(ch))
                    state = 3; // continue fractional part
                else
                    return false;
                break;

            default:
                return false;
        }
    }

    return (state == 1 || state == 3); // integer or float final state
}

// ----------------------------
// Main function
// ----------------------------
int main() {
    string input;
    cout << "Enter a word: ";
    cin >> input;

    if (identifierNFA(input))
        cout << "Accepted: '" << input << "' is an IDENTIFIER (variable).\n";
    else if (numberNFA(input))
        cout << "Accepted: '" << input << "' is a NUMBER.\n";
    else
        cout << "Rejected: '" << input << "' is not a valid token.\n";

    return 0;
}