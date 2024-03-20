#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <chrono>
#include "../h/Maze.h"

class Game {
public:
    Game(int size);
    void play();

private:
    Maze maze;
    int moves;
    
    void updatePosition(int& x, int& y, Direction direction);
};

#endif // GAME_H
