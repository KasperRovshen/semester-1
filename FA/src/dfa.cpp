#include "../h/dfa.h"

template<typename State, typename Symbol>
DFA<State, Symbol>::DFA(vector<Symbol> alphabet, unordered_map<State, unordered_map<Symbol, State>> transitionTable, State initialState, vector<State> finalStates)
    : alphabet(alphabet), transitionTable(transitionTable), initialState(initialState), finalStates(finalStates) {}

template<typename State, typename Symbol>
bool DFA<State, Symbol>::isAccepted(string input) {
    State currentState = initialState;
    for (char c : input) {
        if (find(alphabet.begin(), alphabet.end(), c) == alphabet.end()) {
            cout << "Invalid input character: " << c << endl;
            return false;
        }
        currentState = transitionTable[currentState][c];
    }
    return (find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end());
}