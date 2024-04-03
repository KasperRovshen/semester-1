#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

template<typename State, typename Symbol>
class DFA {
private:
    vector<Symbol> alphabet;
    unordered_map<State, unordered_map<Symbol, State>> transitionTable;
    State initialState;
    vector<State> finalStates;

public:
    DFA(vector<Symbol> alphabet, unordered_map<State, unordered_map<Symbol, State>> transitionTable, State initialState, vector<State> finalStates)
        : alphabet(alphabet), transitionTable(transitionTable), initialState(initialState), finalStates(finalStates) {}

    bool isAccepted(string input) {
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
};

int main() {
    // алфавит, таблицу переходов, начальное и конечное состояния.
    vector<char> alphabet = {'0', '1'};
    unordered_map<char, unordered_map<char, char>> transitionTable = {
        {'A', {{'0', 'B'}, {'1', 'A'}}},
        {'B', {{'0', 'C'}, {'1', 'B'}}},
        {'C', {{'0', 'A'}, {'1', 'C'}}}
    };
    char initialState = 'A';
    vector<char> finalStates = {'B'};

    // экземпляр DFA
    DFA<char, char> dfa(alphabet, transitionTable, initialState, finalStates);

    // Тестовые строки на соответствие DFA
    cout << "Testing strings against the DFA:\n";
    vector<string> testStrings = {"","1", "0", "00", "000", "0000", "00000", "01", "10", "101", "110"};
    for (const string& str : testStrings) {
        cout << "String: " << str << ", Accepted: " << (dfa.isAccepted(str) ? "Yes" : "No") << endl;
    }

    return 0;
}
