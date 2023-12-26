Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}
Deck::~Deck() {}
void Deck::Populate()
{
    Clear();
    // создает стандартную колоду
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
    {
        for (int r = Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}
void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(), m_Cards.end());
}
void Deck::Deal(Hand& aHand)
{
    if(!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout << "Закончились карты." << endl;    
    }
}
void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout << endl;
    // продолжает раздавать карты до тех пор. пока у игрока не случается
    // перебор или пока он хочет взять еще одну карту
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;
        if (aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
}