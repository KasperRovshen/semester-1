/*
Чарыев Бабаровшен

Здравствуйте!
Это программа(если ее можно так назвать), где игрок собирает сокровища в лабиринте.
После того как он собирет все сокровища, игра должна завершиться. Но она не завершается.
Другими словами, я не смог завершить цикл и добавил условие для выхода из игры*/


#include <iostream>
#include <vector>
#include <random>
#include "MazeElement.h"
#include "Wall.h"
#include "Treasures.h"
#include "EmptySpace.h"
#include "Player.h"
#include "Maze.h"
#include "Game.h"


int main() {
    Game game(5);
    game.play();

    return 0;
}
