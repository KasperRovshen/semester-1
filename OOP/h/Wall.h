#ifndef WALL_H
#define WALL_H

#include "../h/MazeElement.h"

class Wall : public MazeElement {
public:
    char getSymbol() const override {
        return '#';
    }
};

#endif // WALL_H
