#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename State, typename Symbol>
class DFA {
private:
    vector<Symbol> alphabet;
    unordered_map<State, unordered_map<Symbol, State>> transitionTable;
    State initialState;
    vector<State> finalStates;

public:
    DFA(vector<Symbol> alphabet, unordered_map<State, unordered_map<Symbol, State>> transitionTable, State initialState, vector<State> finalStates);
    bool isAccepted(string input);
};

#endif /* DFA_H */