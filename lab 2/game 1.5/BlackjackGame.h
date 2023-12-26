#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H

#include "Deck.h"

class BlackjackGame {
public:
    void play();

    ~BlackjackGame();

private:
    int playerScore;
    int dealerScore;

    void dealInitialCards();

    int dealCard(const std::string& participant);

    void displayHands(bool showDealerCard) const;

    void displayHand(int score) const;

    bool playerTurn();

    bool dealerTurn();

    void displayResults() const;

    bool playAgain() const;

    Deck deck;
};

#endif // BLACKJACK_GAME_H
