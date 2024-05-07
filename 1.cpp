/*я не знаю правильно я сделал или нет но решил сделать суффиксный автомат для строки abbab. 
также решил поставить задачу для проверки вхождения строки.*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

template<typename StringType>
class SuffixAutomaton {
private:
    struct State {
        int length; // Длина суффикса
        int link; // Ссылка на состояние, представляющее наибольший суффикс
        map<typename StringType::value_type, int> next; // Переходы из текущего состояния

        State() : length(0), link(-1) {}
    };

    vector<State> states;
    int last;

public:
    SuffixAutomaton(const StringType& s) {
        states.emplace_back(); //начальное состояние
        last = 0;

        for (auto c : s) {
            addCharacter(c);
        }
    }

    void addCharacter(typename StringType::value_type c) {
        int newStateIndex = states.size();
        states.emplace_back();

        int currentState = last;
        last = newStateIndex;

        states[newStateIndex].length = states[currentState].length + 1;
        
        //  переход от текущего состояния к новому состоянию по символу c
        while (currentState != -1 && states[currentState].next.find(c) == states[currentState].next.end()) {
            states[currentState].next[c] = newStateIndex;
            currentState = states[currentState].link;
        }

        if (currentState == -1) {
            states[newStateIndex].link = 0;
        } else {
            int nextState = states[currentState].next[c];
            if (states[currentState].length + 1 == states[nextState].length) {
                states[newStateIndex].link = nextState;
            } else {
                int cloneStateIndex = states.size();//клон состояния для корректной обработки ссылок
                states.emplace_back(states[nextState]);
                states[cloneStateIndex].length = states[currentState].length + 1;

                while (currentState != -1 && states[currentState].next[c] == nextState) {
                    states[currentState].next[c] = cloneStateIndex;
                    currentState = states[currentState].link;
                }

                states[newStateIndex].link = states[nextState].link = cloneStateIndex;
            }
        }
    }
    // Метод для проверки является ли строка p подстрокой s
    bool isSubstring(const StringType& p) {
        int currentState = 0;

        for (auto c : p) {
            if (states[currentState].next.find(c) == states[currentState].next.end()) {
                return false;
            }
            currentState = states[currentState].next[c];
        }

        return true;
    }
};

/*для проверки
-"bab", -"aaa"*/

int main() {
    string s = "abbab";
    string p;
    cout << "Enter string p: ";
    cin >> p;

    SuffixAutomaton<string> sa(s);
    if (sa.isSubstring(p)) {
        cout << "String p is a substring of string s." << endl;
    } else {
        cout << "String p is not a substring of string s." << endl;
    }

    return 0;
}
