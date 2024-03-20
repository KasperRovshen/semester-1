#include "../h/dfa.h"
#include <algorithm>
#include <iostream>

DFA::DFA(std::vector<char> alphabet, std::unordered_map<char, std::unordered_map<char, char>> transitionTable, char initialState, std::vector<char> finalStates)
    : alphabet(alphabet), transitionTable(transitionTable), initialState(initialState), finalStates(finalStates) {}

bool DFA::isAccepted(std::string input) {
    char currentState = initialState;
    for (char c : input) {
        if (find(alphabet.begin(), alphabet.end(), c) == alphabet.end())  {
            std::cout << "Invalid input character: " << c << std::endl;
            return false;
        }
        currentState = transitionTable[currentState][c];
    }
    return (std::find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end());
}
