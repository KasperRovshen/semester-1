#ifndef DFA_H
#define DFA_H

#include <string>
#include <unordered_map>
#include <vector>

class DFA {
private:
    std::vector<char> alphabet;
    std::unordered_map<char, std::unordered_map<char, char>> transitionTable;
    char initialState;
    std::vector<char> finalStates;

public:
    DFA(std::vector<char> alphabet, std::unordered_map<char, std::unordered_map<char, char>> transitionTable, char initialState, std::vector<char> finalStates);
    bool isAccepted(std::string input);
};

#endif // DFA_H
