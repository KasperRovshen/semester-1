#include <iostream>
#include <string>

using namespace std;

class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
    public:
        GenericPlayer(const string& name);
        virtual ~GenericPlayer();
        // показывает. хочет ли игрок продолжать брать карты
        virtual bool IsHitting() const = 0;
        // возвращает значение. если игрок имеет перебор -
        // сумму очков. большую 21
        bool IsBusted() const;
        // объявляет. что игрок имеет перебор
        void Bust() const;
    protected:
        string m_Name;
};
