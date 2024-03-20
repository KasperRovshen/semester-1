#include <iostream>
#include <random>
#include "../h/Maze.h"
#include "../h/Wall.h"
#include "../h/Treasure.h"
#include "../h/EmptySpace.h"
#include "../h/Player.h"


Maze::Maze(int mazeSize) : size(mazeSize), player(nullptr), treasuresRemaining(0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 2);

    for (int i = 0; i < size; ++i) {
        std::vector<std::unique_ptr<MazeElement>> row;
        for (int j = 0; j < size; ++j) {
            int randValue = distrib(gen);
            switch (randValue) {
                case 0:
                    row.push_back(std::make_unique<Wall>());
                    break;
                case 1:
                    row.push_back(std::make_unique<Treasure>());
                    ++treasuresRemaining;
                    break;
                case 2:
                    row.push_back(std::make_unique<EmptySpace>());
                    break;
            }
        }
        maze.push_back(std::move(row));
    }

    std::uniform_int_distribution<> distribCoords(0, size - 1);
    int playerX = distribCoords(gen);
    int playerY = distribCoords(gen);
    player = std::make_unique<Player>();
    maze[playerX][playerY] = std::make_unique<Player>();
}


void Maze::printMaze() const {
    for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << maze[i][j]->getSymbol() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    
}

bool Maze::isTreasureFound() {
     int playerX = getPlayerX();
        int playerY = getPlayerY();

        MazeElement* currentElement = getElement(playerX, playerY).get();
        if (currentElement->getSymbol() == 'T') {
            if (treasuresRemaining > 0) {
                --treasuresRemaining;
                return true;
            }
        }
        return false;
}

int Maze::getPlayerX() const {
    for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (maze[i][j]->getSymbol() == 'P') {
                    return i;
                }
            }
        }
        return -1;
}

int Maze::getPlayerY() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (maze[i][j]->getSymbol() == 'P') {
                return j;
            }
        }
    }
}

std::unique_ptr<MazeElement>& Maze::getElement(int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size) {
            return maze[x][y];
        } else {
            return maze[0][0]; // Return a reference to a default element
    }
}

bool Maze::areAllTreasuresFound() const {
     return treasuresRemaining == 0;
}

void Maze::updatePlayerPosition(int newX, int newY) {
        int oldX = getPlayerX();
        int oldY = getPlayerY();

        maze[oldX][oldY] = std::make_unique<EmptySpace>();
        maze[newX][newY] = std::make_unique<Player>();
}
