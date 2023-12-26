class Game {
public:
    Game(int size) : maze(size) {}

    void play() {
    while (true) {
        maze.printMaze();

        if (maze.areAllTreasuresFound()) {
            std::cout << "Поздравляем! Вы нашли все сокровища.\n";
            break;  // Добавляем выход из цикла, если все сокровища найдены
        }

        std::cout << "Выберите направление движения (u(вверх)/d(вниз)/l(налево)/r(направо)):""\nq/выход из игры." << std::endl;
        char direction;
        std::cin >> direction;

        if (direction == 'q') {
                std::cout << "Выход из игры.\n";
                break;
            }

        int newX = maze.getPlayerX();
        int newY = maze.getPlayerY();

        switch (direction) {
            case 'u':
                --newX;
                break;
            case 'd':
                ++newX;
                break;
            case 'l':
                --newY;
                break;
            case 'r':
                ++newY;
                break;
            case 'q':
                std::cout << "Выход из игры.\n";
                return;
            default:
                std::cout << "Неверное направление. Попробуйте еще раз.\n";
                continue;
        }

        MazeElement* newElement = maze.getElement(newX, newY);
        if (newElement->getSymbol() == '#') {
            std::cout << "Вы не можете пройти сквозь стену!\n";
        } else {
            maze.updatePlayerPosition(newX, newY);

            if (maze.areAllTreasuresFound()) {
                std::cout << "Вы нашли сокровище!\n";
                break;
            }
        }
    }
}


private:
    Maze maze;
};


