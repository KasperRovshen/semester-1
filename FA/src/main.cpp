#include <iostream>
#include "../h/dfa.h"

int main() {
    std::vector<char> alphabet;
    std::unordered_map<char, std::unordered_map<char, char>> transitionTable;
    char initialState;
    std::vector<char> finalStates;

    // Accepting user-defined alphabet
    std::string alphabetStr;
    std::cout << "Enter the alphabet (without spaces): ";
    std::cin >> alphabetStr;
    for (char c : alphabetStr) {
        alphabet.push_back(c);
    }

    // Accepting transition table
    std::cout << "Enter the transition table (use 'x' for no transition):\n";
    for (char state : alphabet) {
        std::cout << "Transition for state " << state << ":" << std::endl;
        for (char symbol : alphabet) {
            std::cout << "  Input " << symbol << ": ";
            char nextState;
            std::cin >> nextState;
            transitionTable[state][symbol] = nextState;
        }
    }

    // Accepting initial state
    std::cout << "Enter the initial state: ";
    std::cin >> initialState;

    // Accepting final states
    std::string finalStatesStr;
    std::cout << "Enter the final states (without spaces): ";
    std::cin >> finalStatesStr;
    for (char c : finalStatesStr) {
        finalStates.push_back(c);
    }

    // Creating the DFA instance
    DFA dfa(alphabet, transitionTable, initialState, finalStates);

    // Accepting input strings and checking if they are accepted by the DFA
    while (true) {
        std::string input;
        std::cout << "Enter a string over the alphabet " << alphabetStr << " (enter 'q' to quit): ";
        std::cin >> input;
        if (input == "q") {
            break;
        }
        if (dfa.isAccepted(input)) {
            std::cout << "Accepted" << std::endl;
        } else {
            std::cout << "Rejected" << std::endl;
        }
    }

    return 0;
}
