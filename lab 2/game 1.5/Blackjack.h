#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include "Card.h"

class BlackjackCard : public Card {
public:
    BlackjackCard(Rank r, Suit s);

    int getValue() const override;

    void display() const override;
};

#endif // BLACKJACK_CARD_H
