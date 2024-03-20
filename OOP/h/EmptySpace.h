#ifndef EMPTY_SPACE_H
#define EMPTY_SPACE_H

#include "../h/MazeElement.h"

class EmptySpace : public MazeElement {
public:
    char getSymbol() const override {
        return ' ';
    }
};

#endif // EMPTY_SPACE_H
