#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class DFA {
public:
    DFA(std::vector<std::string> states, std::string start_state, std::vector<std::string> accept_states, std::map<std::string, std::map<char, std::string>> transition_table);

    bool accepts(std::string word);

private:
    std::vector<std::string> states;
    std::string start_state;
    std::vector<std::string> accept_states;
    std::map<std::string, std::map<char, std::string>> transition_table;

    bool isValidTransitionTable();
};

DFA::DFA(std::vector<std::string> states, std::string start_state, std::vector<std::string> accept_states, std::map<std::string, std::map<char, std::string>> transition_table) {
    this->states = states;
    this->start_state = start_state;
    this->accept_states = accept_states;
    this->transition_table = transition_table;

    if (!isValidTransitionTable()) {
        std::cerr << "Error: Invalid transition table." << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool DFA::accepts(std::string word) {
    std::string current_state = start_state;

    for (char symbol : word) {
        if (transition_table[current_state].count(symbol) == 0) {
            return false;
        }
        current_state = transition_table[current_state][symbol];
    }

    return std::find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end();
}

bool DFA::isValidTransitionTable() {
    for (const auto& state_entry : transition_table) {
        const std::string& current_state = state_entry.first;
        const std::map<char, std::string>& transitions = state_entry.second;

        for (const auto& transition : transitions) {
            char symbol = transition.first;
            const std::string& next_state = transition.second;

            // Проверка наличия состояния в списке состояний
            if (std::find(states.begin(), states.end(), current_state) == states.end() ||
                std::find(states.begin(), states.end(), next_state) == states.end()) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::vector<std::string> states = {"q0", "q1", "q2"};
    std::string start_state = "q0";
    std::vector<std::string> accept_states = {"q2"};
    std::map<std::string, std::map<char, std::string>> transition_table = {
        {"q0", {{'a', "q1"}, {'b', "q0"}}},
        {"q1", {{'a', "q0"}, {'b', "q2"}}},
        {"q2", {{'a', "q2"}, {'b', "q0"}}},
    };

    DFA dfa(states, start_state, accept_states, transition_table);

    std::cout << dfa.accepts("aaab") << std::endl; // должно вывести: 1
    std::cout << dfa.accepts("baba") << std::endl; // должно вывести: 0

    return 0;
}
