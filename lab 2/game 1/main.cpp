// Играет упрощенную версию игры Blackjack: от одного до семи игроков

#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Game.h"
#include "GenericPlayer.h"
#include "Hand.h"

using namespace std;


// прототипы функций(объявления функций перегруженного оператора operator«())
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);


int main () {
    cout << "\t\tДобро пожаловать в BlackJack!\n";
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7) {
        cout << "Сколько игроков? (1-7): ";
        cin >> numPlayers;
    }
    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Введите имя игрока:";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << "Хочешь сыграть еще раз? (y/n): ";
        cin >> again;
        cout << endl;
    }
    return 0;    
}


// перегружает оператор«, чтобы получить возможность отправить
// объект типа Card в поток cout
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string SUITS[] = {"C", "D", "H", "S"};
    if (aCard.m_IsFaceUp)
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else
    {
        os << "XX";
    }
    return os;
}