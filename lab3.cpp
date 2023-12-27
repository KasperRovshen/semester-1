#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

class DFA {
private:
    std::map<char, int> alphabet_map;
    std::vector<std::vector<int>> transition_table;
    int initial_state;
    std::vector<int> final_states;

public:
    // Конструктор принимает алфавит, таблицу переходов, начальное состояние и конечные состояния
    DFA(const std::vector<char>& alphabet,
        const std::vector<std::vector<int>>& transition_table,
        int initial_state, const std::vector<int>& final_states)
        //alphabet_map: отображение символов алфавита в их индексы.
        //transition_table: таблица переходов между состояниями. 
        //initial_state: начальное состояние. 
        //final_states: вектор конечных состояний.                          
        : alphabet_map(), transition_table(transition_table), 
          initial_state(initial_state), final_states(final_states) {

        // Переносим алфавит в map
        for (size_t i = 0; i < alphabet.size(); ++i) {
            alphabet_map[alphabet[i]] = i;
        }
    }
    //Метод Accepts, который проверяет, принимается ли заданное слово конечным автоматом.
    bool Accepts(const std::string& word) const {
        int current_state = initial_state;
  
        for (size_t i = 0; i < word.size(); ++i) {
            char symbol = word[i];

            // Проверка наличия символа в алфавите
            if (alphabet_map.find(symbol) == alphabet_map.end()) {
                std::cerr << "Error: Symbol '" << symbol << "' is not in the alphabet." << std::endl;
                return false; // Неизвестный символ.
            }

            // Переход к новому состоянию
            int symbol_index = alphabet_map.at(symbol);

            // Проверка на выход за пределы размеров вектора transition_table
            if (current_state < 0 || static_cast<size_t>(current_state) >= transition_table.size()) {
                std::cerr << "Error: Invalid current state index." << std::endl;
                return false;
            }

            // Проверка на выход за пределы размеров вложенного вектора transition_table
            if (symbol_index < 0 || static_cast<size_t>(symbol_index) >= transition_table[current_state].size()) {
                std::cerr << "Error: Invalid symbol index in the transition table." << std::endl;
                return false;
            }

            current_state = transition_table[current_state][symbol_index];
        }

        // Проверка на выход за пределы размеров вектора final_states
        if (std::find(final_states.begin(), final_states.end(), current_state) == final_states.end()) {
            std::cerr << "Error: Invalid final state." << std::endl;
            return false;
        }

        return true;
    }
};

int main() {
    // Ввод алфавита и таблицы переходов от пользователя
    std::cout << "Enter the alphabet (no spaces): ";
    std::string alphabet_input;
    std::cin >> alphabet_input;

    std::vector<char> alphabet(alphabet_input.begin(), alphabet_input.end());

    std::cout << "Enter the number of states: ";
    int num_states;
    std::cin >> num_states;

    std::vector<std::vector<int>> transition_table(num_states, std::vector<int>(alphabet.size()));

    std::cout << "Enter the transition table:" << std::endl;
    for (int i = 0; i < num_states; ++i) {
        for (size_t j = 0; j < alphabet.size(); ++j) {
            std::cout << "Transition from state " << i << " on symbol '" << alphabet[j] << "': ";
            std::cin >> transition_table[i][j];
        }
    }

    int initial_state;
    std::cout << "Enter the initial state: ";
    std::cin >> initial_state;

    std::cout << "Enter the number of final states: ";
    int num_final_states;
    std::cin >> num_final_states;

    std::vector<int> final_states(num_final_states);

    std::cout << "Enter the final states:" << std::endl;
    for (int i = 0; i < num_final_states; ++i) {
        std::cout << "Final state " << i << ": ";
        std::cin >> final_states[i];
    }

    // Создание экземпляра DFA с заданными пользователем данными
    DFA dfa(alphabet, transition_table, initial_state, final_states);

    // Проверка нескольких слов
    std::string word1 = "ab";
    std::string word2 = "aab";
    std::string word3 = "bb";

    // Проверка и вывод результата
    if (dfa.Accepts(word1)) {
        std::cout << "Accepted" << std::endl;
    } else {
        std::cout << "Rejected" << std::endl;
    }

    if (dfa.Accepts(word2)) {
        std::cout << "Accepted" << std::endl;
    } else {
        std::cout << "Rejected" << std::endl;
    }

    if (dfa.Accepts(word3)) {
        std::cout << "Accepted" << std::endl;
    } else {
        std::cout << "Rejected" << std::endl;
    }

    return 0;
}
