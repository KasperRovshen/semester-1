#include "Player.h"

Player::Player(const string name) : GenericPlayer(name) {}
Player::~Player() {}
bool Player::IsHitting() const
{
    cout << m_Name << " . do you want a hit? (y/n) ";
    char answer;
    cin >> answer;
    return(answer == 'y'|| answer == 'Y');
}
void Player::Win() const
{
    cout << m_Name << " wins!" << endl;
}
void Player::Lose() const
{
    cout << m_Name << " loses!" << endl;
}
void Player::Push() const
{
    cout << m_Name << " pushes!" << endl;
}
