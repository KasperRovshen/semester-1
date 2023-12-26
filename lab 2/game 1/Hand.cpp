#include "Hand.h"

Hand::Hand()
{
    m_Cards.reserve(7);
}
Hand::~Hand()
{
    Clear();
}
void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}
void Hand::Clear()
{
    // проходит по вектору. освобождая всю память в куче
    vector<Card*>::iterator iter = m_Cards.begin();
    while (iter!= m_Cards.end()) {
        delete *iter;
        iter = m_Cards.erase(iter);
    }
    // очищает вектор указателей
    m_Cards.clear();
}
int Hand::GetTotal() const
{
    // если карт в руке нет. возвращает значение О
    if (m_Cards.empty())
    {
        return 0;
    }
    // если первая карта имеет значение О. то она лежит рубашкой вверх:
    // вернуть значение О
    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }
    // находит сумму очков всех карт. каждый туз дает 1 очко
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter!= m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }
    // определяет. держит ли рука туз
    bool isAce = false;
    for (iter = m_Cards.begin(); iter!= m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            isAce = true;
            
        }
    }
    // если рука держит туз и сумма довольно маленькая. туз дает 11 очков
    if (isAce && total <= 11)
    {
        // добавляем только 10 очков. поскольку мы уже добавили
        // за каждый туз по одному очку
        total += 10;
    }
    return total;    
}
