#include "Game.h"

Game::Game(const vector<string>& names)
{
    // создает вектор игроков из вектора с именами
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName!= names.end(); ++pName)
    {
        m_Players.push_back(new Player(*pName));
    }
    
    // засевает генератор случайных чисел
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Shuffle();
    m_Deck.Populate();
}
Game::~Game() 
{}
void Game::Play()
{
    // раздает каждому по две стартовые карты
    std::vector<Player *>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (auto pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(**pPlayer);
        }
        m_Deck.Deal(m_Dealer);
    }
    // прячет первую карту дилера
    m_Dealer.FlipFirstCard();
    // открывает руки всех игроков    
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << **pPlayer << endl;
    }
    cout << m_Dealer << endl;

    // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(**pPlayer);
    }

    // показывает первую карту дилера
    m_Dealer.FlipFirstCard();
    cout << endl << m_Dealer;
    // раздает дилеру дополнительные карты
    m_Deck.AdditionalCards(m_Dealer);
    if (m_Dealer.IsBusted())
    {
        // все кто остался в игре побеждают
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!((**pPlayer).IsBusted()))
            {
                (*pPlayer)->Win();
            }
        }
    }
    else
    {
        // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!((**pPlayer).IsBusted()))
            {
                if ((**pPlayer).GetTotal() > m_Dealer.GetTotal())
                {
                    (*pPlayer)->Win();
                }
                else if ((**pPlayer).GetTotal() == m_Dealer.GetTotal())
                {
                    (*pPlayer)->Push();
                }
                else
                {
                    (*pPlayer)->Lose();
                }
            }
        }
    }

    // очищает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        (*pPlayer)->Clear();
    }
    m_Dealer.Clear();
}

