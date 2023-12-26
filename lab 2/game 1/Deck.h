#include <iostream>
#include "GenericPlayer.h"
#include "Hand.h"

using namespace std;

class Deck : public Hand
{
    public:
        Deck();
        virtual ~Deck();
        // создает стандартную колоду из 52 карт
        void Populate();
        // тасует карты
        void Shuffle();
        // раздает одну карту в руку
        void Deal(Hand& aHand);
        // дает дополнительные карты игроку
        void AdditionalCards(GenericPlayer& aGenericPlayer);
};