#include "Card.h"

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}
    int Card::GetValue() const {
        // если карта перевернута лицом вниз. ее значение равно О
        int value = 0;
        if (m_IsFaceUp) {
            // значение - это число. указанное на карте
            value = m_Rank; 
            // значение равно 10 для открытых карт
            if (value == 10) {
                value = 10;
            }
        }
        return value;
    }
void Card::Flip() {
m_IsFaceUp =!(m_IsFaceUp);
}