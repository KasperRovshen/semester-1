#include <iostream>
#include <string>
#include "GenericPlayer.h"

using namespace std;

class Dealer : public GenericPlayer {
    public:
        Dealer(const string name = "");
        virtual ~Dealer();
        // показывает. хочет ли игрок продолжать брать карты
        virtual bool IsHitting() const;
        // переворачивает первую карту
        void FlipFirstCard() const;
        
};