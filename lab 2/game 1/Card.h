#include <iostream>

using namespace std;

class Card{
    public:
        enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
        enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
        // перегружаем оператор«, чтобы можно было отправить объект
        // типа Card в стандартный поток вывода
        friend ostream& operator<<(ostream& os, const Card& card);
        Card(rank r = ACE, suit s = SPADES, bool ifu = true);
        // возвращает значение карты. от 1 до 11
        int GetValue() const;
        // переворачивает карту: карта. лежащая лицом вверх.
        // переворачивается лицом вниз и наоборот
        void Flip();
    private:
        rank m_Rank;
        suit m_Suit;
        bool m_IsFaceUp;
    };