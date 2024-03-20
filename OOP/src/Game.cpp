#include <iostream>
#include "../h/Game.h"
#include "../h/Maze.h"

Game::Game(int size) : maze(size), moves(0) {}

void Game::play() {
    while (true) {
            maze.printMaze();

            if (maze.areAllTreasuresFound()) {
                std::cout << "Congratulations! You found all treasures." << std::endl;
                break;
            }

            std::cout << "Current position: (" << maze.getPlayerX() << ", " << maze.getPlayerY() << ")" << std::endl;
            std::cout << "Choose direction (u/d/l/r/q): " << std::endl;
            char direction;
            std::cin >> direction;

            Direction moveDirection = Direction::NONE;
            switch (direction) {
                case 'u':
                    moveDirection = Direction::UP;
                    break;
                case 'd':
                    moveDirection = Direction::DOWN;
                    break;
                case 'l':
                    moveDirection = Direction::LEFT;
                    break;
                case 'r':
                    moveDirection = Direction::RIGHT;
                    break;
                 case 'q':
                    moveDirection = Direction::QUIT;                 
                    std::cout << "Quitting..." << std::endl;
                    return;
                default:
                    std::cout << "Invalid direction. Please try again." << std::endl;
                    continue;
            }

            int newX = maze.getPlayerX();
            int newY = maze.getPlayerY();
            updatePosition(newX, newY, moveDirection);

            if (maze.areAllTreasuresFound()) {
                std::cout << "Congratulations! You found all treasures." << std::endl;
                break;
            }

            if (newX == maze.getPlayerX() && newY == maze.getPlayerY()) {
                std::cout << "You cannot move in that direction." << std::endl;
            }

            ++moves;
        }
        std::cout << "Total moves: " << moves << std::endl;
}

void Game::updatePosition(int& x, int& y, Direction direction) {
    switch (direction) {
            case Direction::UP:
                --x;
                break;
            case Direction::DOWN:
                ++x;
                break;
            case Direction::LEFT:
                --y;
                break;
            case Direction::RIGHT:
                ++y;
                break;
            default:
                break;
        }

    MazeElement* newElement = maze.getElement(x, y).get();        if (newElement->getSymbol() == '#') {
     // Wall, cannot move
    } else {
        maze.updatePlayerPosition(x, y);
        if (maze.isTreasureFound()) {
            std::cout << "You found a treasure!" << std::endl;
        }
    }
}

