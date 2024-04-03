#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../h/dfa.h"

using namespace std;

int main() {
    // Define the alphabet, transition table, initial state, and final states
    vector<char> alphabet = {'0', '1'};
    unordered_map<char, unordered_map<char, char>> transitionTable = {
        {'A', {{'0', 'B'}, {'1', 'A'}}},
        {'B', {{'0', 'C'}, {'1', 'B'}}},
        {'C', {{'0', 'A'}, {'1', 'C'}}}
    };
    char initialState = 'A';
    vector<char> finalStates = {'A'};

    // Create the DFA instance
    DFA<char, char> dfa(alphabet, transitionTable, initialState, finalStates);

    // Test strings against the DFA
    cout << "Testing strings against the DFA:\n";
    vector<string> testStrings = {"", "0", "00", "000", "0000", "00000", "01", "10", "101", "110"};
    for (const string& str : testStrings) {
        cout << "String: " << str << ", Accepted: " << (dfa.isAccepted(str) ? "Yes" : "No") << endl;
    }

    return 0;
}
