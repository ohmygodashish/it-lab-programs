/*
Implement NFAs to recognize relational operators, arithmetic operators, parenthesis, 
and white space in lexical analysis.
*/

#include <bits/stdc++.h>
using namespace std;

// ----------------------------
// NFA for Relational Operators
// ----------------------------
bool relationalNFA(const string &word) {
    int state = 0;

    for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        switch (state) {
            case 0:
                if (ch == '>' || ch == '<' || ch == '=' || ch == '!')
                    state = 1;
                else
                    return false;
                break;
            case 1:
                if (ch == '=')
                    state = 2; // e.g., >=, <=, ==, !=
                else if (word.size() == 1)
                    return true; // single-char operator > or <
                else
                    return false;
                break;
            default:
                return false;
        }
    }

    return (state == 1 && word.size() == 1) || (state == 2);
}

// ----------------------------
// NFA for Arithmetic Operators
// ----------------------------
bool arithmeticNFA(const string &word) {
    if (word.size() != 1) return false;
    char ch = word[0];
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

// ----------------------------
// NFA for Parentheses
// ----------------------------
bool parenthesisNFA(const string &word) {
    if (word.size() != 1) return false;
    char ch = word[0];
    return (ch == '(' || ch == ')');
}

// ----------------------------
// NFA for Whitespace
// ----------------------------
bool whitespaceNFA(const string &word) {
    for (char ch : word)
        if (!(ch == ' ' || ch == '\t' || ch == '\n'))
            return false;
    return true;
}

// ----------------------------
// Main Function
// ----------------------------
int main() {
    string input;
    cout << "Enter a token: ";
    getline(cin, input); // allows spaces too

    if (relationalNFA(input))
        cout << "Accepted: '" << input << "' is a RELATIONAL OPERATOR.\n";
    else if (arithmeticNFA(input))
        cout << "Accepted: '" << input << "' is an ARITHMETIC OPERATOR.\n";
    else if (parenthesisNFA(input))
        cout << "Accepted: '" << input << "' is a PARENTHESIS.\n";
    else if (whitespaceNFA(input))
        cout << "Accepted: '" << input << "' is WHITESPACE.\n";
    else
        cout << "Rejected: '" << input << "' is not a valid token.\n";

    return 0;
}