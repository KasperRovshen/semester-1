#include "BlackjackGame.h"
#include <iostream>

void BlackjackGame::play() {
    while (true) {
        playerScore = 0;
        dealerScore = 0;

        dealInitialCards();
        displayHands(true);

        while (playerTurn()) {
            displayHands(true);
        }

        while (dealerTurn()) {
            displayHands(false);
        }

        displayResults();
        if (!playAgain()) {
            break;
        }
    }
}

BlackjackGame::~BlackjackGame() {
    // Ничего особенного не нужно для деструктора в данном случае
}

void BlackjackGame::dealInitialCards() {
    playerScore += dealCard("You");
    dealerScore += dealCard("Dealer");
    playerScore += dealCard("You");
    dealerScore += dealCard("Dealer");
}

int BlackjackGame::dealCard(const std::string& participant) {
    Card* card = deck.dealCard();
    if (card) {
        std::cout << participant << " got a ";
        card->display();
        std::cout << std::endl;

        int value = card->getValue();
        delete card;
        return value;
    } else {
        // Карты закончились, можно обработать ситуацию по-другому
        return 0;
    }
}

void BlackjackGame::displayHands(bool showDealerCard) const {
    std::cout << "Your hand: ";
    displayHand(playerScore);
    std::cout << std::endl;

    std::cout << "Dealer's hand: ";
    if (showDealerCard) {
        displayHand(dealerScore);
    } else {
        std::cout << "??";
    }
    std::cout << std::endl;
}

void BlackjackGame::displayHand(int score) const {
    std::cout << "Score: " << score << " ";
}

bool BlackjackGame::playerTurn() {
    char choice;
    do {
        std::cout << "Do you want to hit (h) or stand (s)? ";
        std::cin >> choice;
    } while (choice != 'h' && choice != 's');

    if (choice == 'h') {
        playerScore += dealCard("You");
        return true;
    } else {
        return false;
    }
}

bool BlackjackGame::dealerTurn() {
    if (dealerScore < 17) {
        dealerScore += dealCard("Dealer");
        return true;
    } else {
        return false;
    }
}

void BlackjackGame::displayResults() const {
    displayHands(false);

    if (playerScore > 21 || (dealerScore <= 21 && dealerScore > playerScore)) {
        std::cout << "Dealer wins!" << std::endl;
    } else if (dealerScore > 21 || playerScore > dealerScore) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "It's a tie!" << std::endl;
    }
}

bool BlackjackGame::playAgain() const {
    char choice;
    do {
        std::cout << "Do you want to play again? (y/n) ";
        std::cin >> choice;
    } while (choice != 'y' && choice != 'n');

    return choice == 'y';
}
