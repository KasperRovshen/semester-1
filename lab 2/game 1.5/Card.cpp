#include "Card.h"

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

int Card::getValue() const {
    if (rank > 10) {
        return 10;
    } else {
        return rank;
    }
}

void Card::display() const {
    switch (rank) {
        case ACE: std::cout << 'A'; break;
        case JACK: std::cout << 'J'; break;
        case QUEEN: std::cout << 'Q'; break;
        case KING: std::cout << 'K'; break;
        default: std::cout << rank; break;
    }

    switch (suit) {
        case CLUBS: std::cout << 'C'; break;
        case DIAMONDS: std::cout << 'D'; break;
        case HEARTS: std::cout << 'H'; break;
        case SPADES: std::cout << 'S'; break;
    }
}

Card::~Card() {}
