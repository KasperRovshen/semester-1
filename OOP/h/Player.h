#ifndef PLAYER_H
#define PLAYER_H

#include "../h/MazeElement.h"

class Player : public MazeElement {
public:
    char getSymbol() const override {
        return 'P';
    }
};

#endif // PLAYER_H
