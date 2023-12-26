#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
public:
    Deck();

    ~Deck();

    void shuffle();

    Card* dealCard();

private:
    std::vector<Card*> cards;
};

#endif // DECK_H
