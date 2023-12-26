#include "BlackjackCard.h"

BlackjackCard::BlackjackCard(Rank r, Suit s) : Card(r, s) {}

int BlackjackCard::getValue() const {
    if (rank == ACE) {
        // В блэкджеке туз может быть 1 или 11, в зависимости от ситуации
        return 11;
    } else {
        return Card::getValue();
    }
}

void BlackjackCard::display() const {
    Card::display();  // Вызываем метод display() из базового класса
}
