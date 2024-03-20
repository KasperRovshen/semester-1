#ifndef TREASURE_H
#define TREASURE_H

#include "../h/MazeElement.h"

class Treasure : public MazeElement {
public:
    char getSymbol() const override {
        return 'T';
    }
};

#endif // TREASURE_H
