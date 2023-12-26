#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class Game {
    public:
        Game(const vector<string>& names);
        ~Game();
        // проводит игру в Blackjack
        void Play();
    private:
        Deck m_Deck;
        Dealer m_Dealer;
        vector<Player*> m_Players;
};