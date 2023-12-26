#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank r, Suit s);

    virtual int getValue() const;

    virtual void display() const;

    virtual ~Card(); // Добавляем виртуальный деструктор для корректного удаления при использовании наследования
    
protected:
    Rank rank;
    Suit suit;
};

#endif // CARD_H
