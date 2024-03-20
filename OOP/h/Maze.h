#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <memory>
#include <random>
#include "../h/Player.h"
#include "../h/Treasure.h"
#include "../h/Wall.h"
#include "../h/EmptySpace.h"

enum class Direction { UP, DOWN, LEFT, RIGHT, NONE, QUIT };

class Maze {
public:
    Maze(int mazeSize);
    void printMaze() const;
    bool isTreasureFound();
    int getPlayerX() const;
    int getPlayerY() const;
    std::unique_ptr<MazeElement>& getElement(int x, int y);
    bool areAllTreasuresFound() const;
    void updatePlayerPosition(int newX, int newY);

private:
    int size;
    std::vector<std::vector<std::unique_ptr<MazeElement>>> maze;
    std::unique_ptr <Player> player;
    int treasuresRemaining;
};

#endif // MAZE_H
