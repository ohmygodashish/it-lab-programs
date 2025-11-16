/*
Write a program to generate tokens for the high-level source code: while (ab>=a1+b1)
*/

#include <bits/stdc++.h>
using namespace std;

// Helper functions
bool isKeyword(const string &word) {
    vector<string> keywords = {"while", "if", "else", "for", "int", "float", "return", "void"};
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

bool isOperator(char c) {
    string ops = "+-*/%=<>!";
    return ops.find(c) != string::npos;
}

bool isDelimiter(char c) {
    string delims = "();{}[],";
    return delims.find(c) != string::npos;
}

// Main tokenization logic
void generateTokens(string code) {
    cout << left << setw(20) << "TOKEN" << "TYPE\n";
    cout << string(35, '-') << "\n";

    for (size_t i = 0; i < code.length();) {
        // Skip spaces
        if (isspace(code[i])) {
            i++;
            continue;
        }

        // Identifier or keyword
        if (isalpha(code[i])) {
            string word;
            while (isalnum(code[i])) {
                word += code[i];
                i++;
            }
            if (isKeyword(word))
                cout << setw(20) << word << "Keyword\n";
            else
                cout << setw(20) << word << "Identifier\n";
        }

        // Numbers
        else if (isdigit(code[i])) {
            string num;
            while (isdigit(code[i])) {
                num += code[i];
                i++;
            }
            cout << setw(20) << num << "Number\n";
        }

        // Operators (including >=, <=, ==, !=)
        else if (isOperator(code[i])) {
            string op(1, code[i]);
            if ((code[i] == '>' || code[i] == '<' || code[i] == '=' || code[i] == '!') && code[i + 1] == '=') {
                op += '=';
                i += 2;
            } else {
                i++;
            }
            cout << setw(20) << op << "Operator\n";
        }

        // Delimiters
        else if (isDelimiter(code[i])) {
            cout << setw(20) << code[i] << "Delimiter\n";
            i++;
        }

        // Unknown character
        else {
            cout << setw(20) << code[i] << "Unknown\n";
            i++;
        }
    }
}

int main() {
    string code;
    cout << "Enter source code: ";
    getline(cin, code);

    cout << "\nGenerated Tokens:\n";
    generateTokens(code);

    return 0;
}