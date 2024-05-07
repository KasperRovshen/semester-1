проверено - E

#include <iostream>
#include "../h/Game.h"

int main() {
    try {
        Game game(5);
        game.play();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
