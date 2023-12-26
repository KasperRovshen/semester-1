class Maze {
public:
    Maze(int mazeSize) : size(mazeSize), player(nullptr), treasuresRemaining(0) {
        // Инициализация генератора случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);

        // Инициализация лабиринта с элементами
        for (int i = 0; i < size; ++i) {
            std::vector<MazeElement*> row;
            for (int j = 0; j < size; ++j) {
                int randValue = distrib(gen);  // 0: Wall, 1: Treasure, 2: EmptySpace
                switch (randValue) {
                    case 0:
                        row.push_back(new Wall());
                        break;
                    case 1:
                        row.push_back(new Treasure());
                        ++treasuresRemaining;  // Увеличиваем количество сокровищ
                        break;
                    case 2:
                        row.push_back(new EmptySpace());
                        break;
                }
            }
            maze.push_back(row);
        }

        // Размещение игрока в начальной позиции
        std::uniform_int_distribution<> distribCoords(0, size - 1);
        int playerX = distribCoords(gen);
        int playerY = distribCoords(gen);
        player = new Player();
        maze[playerX][playerY] = player;
    }

    ~Maze() {
        // Очистка выделенной памяти
        for (auto& row : maze) {
            for (auto& element : row) {
                delete element;
            }
        }
    }

    void printMaze() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << maze[i][j]->getSymbol() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool isTreasureFound() {
        int playerX = getPlayerX();
        int playerY = getPlayerY();

        MazeElement* currentElement = getElement(playerX, playerY);
        if (currentElement->getSymbol() == 'T') {
            if (treasuresRemaining > 0) {
                --treasuresRemaining;
                return true;
            }
        }
        return false;
    }

    int getPlayerX() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (maze[i][j] == player) {
                    return i;
                }
            }
        }
        return -1;  // Игрок не найден
    }

    int getPlayerY() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (maze[i][j] == player) {
                    return j;
                }
            }
        }
        return -1;  // Игрок не найден
    }

    MazeElement* getElement(int x, int y) const {
        if (x >= 0 && x < size && y >= 0 && y < size) {
            return maze[x][y];
        } else {
            // Если координаты выходят за пределы лабиринта, вернем стену
            return new Wall();
        }
    }

    bool areAllTreasuresFound() const {
        return treasuresRemaining == 0;
    }

    void updatePlayerPosition(int newX, int newY) {
        int oldX = getPlayerX();
        int oldY = getPlayerY();

        // Обновление позиции игрока в лабиринте
        maze[oldX][oldY] = new EmptySpace();
        maze[newX][newY] = player;
    }

private:
    int size;
    std::vector<std::vector<MazeElement*>> maze;
    Player* player;
    int treasuresRemaining;
};
