Dealer::Dealer(const string name) : GenericPlayer(name) {}
Dealer::~Dealer() {}
bool Dealer::IsHitting() const
{
    return (GetTotal() <= 16);
}
void House::FlipFirstCard() const
{
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "Нет карты, которую можно перевернуть" << endl;
    }
}
