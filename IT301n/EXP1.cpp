/*
Implement a NFA to recognize keywords in lexical analysis 
(utilize a main program and function calls for the NFA; employ a switch/case statement within the NFA).
*/

#include <bits/stdc++.h>
using namespace std;

// Function to simulate NFA for keywords using switch/case
bool keywordNFA(const string &word) {
int state = 0;

for (int i = 0; i < word.size(); i++) {
char ch = word[i];
switch (state) {

// ---------- Starting State ----------
case 0:
if (ch == 'i') state = 1;        // could be "if" or "int"
else if (ch == 'e') state = 10;  // could be "else"
else if (ch == 'w') state = 20;  // could be "while"
else if (ch == 'f') state = 30;  // could be "for"
else return false;
break;

// ---------- Keyword: if / int ----------
case 1:
if (ch == 'f') state = 2;        // "if"
else if (ch == 'n') state = 3;   // "int"
else return false;
break;

case 3:
if (ch == 't') state = 4;        // "int"
else return false;
break;

// ---------- Keyword: else ----------
case 10:
if (ch == 'l') state = 11;
else return false;
break;
case 11:
if (ch == 's') state = 12;
else return false;
break;
case 12:
if (ch == 'e') state = 13;
else return false;
break;

// ---------- Keyword: while ----------
case 20:
if (ch == 'h') state = 21;
else return false;
break;
case 21:
if (ch == 'i') state = 22;
else return false;
break;
case 22:
if (ch == 'l') state = 23;
else return false;
break;
case 23:
if (ch == 'e') state = 24;
else return false;
break;

// ---------- Keyword: for ----------
case 30:
if (ch == 'o') state = 31;
else return false;
break;
case 31:
if (ch == 'r') state = 32;
else return false;
break;

default:
return false;
}
}

// ---------- Final State Check ----------
switch (state) {
case 2:  // if
case 4:  // int
case 13: // else
case 24: // while
case 32: // for
return true;
default:
return false;
}
}

int main() {
string input;
cout << "Enter a word: ";
cin >> input;

if (keywordNFA(input))
cout << "Accepted: '" << input << "' is a keyword.\n";
else
cout << "Rejected: '" << input << "' is not a keyword.\n";

return 0;
}

