#include "Deck.h"
#include <algorithm>

Deck::Deck() {
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
        for (int r = Card::ACE; r <= Card::KING; ++r) {
            cards.push_back(new BlackjackCard(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
        }
    }
    shuffle();
}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
}

void Deck::shuffle() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(cards.begin(), cards.end());
}

Card* Deck::dealCard() {
    if (cards.empty()) {
        return nullptr;
    }

    Card* dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}
