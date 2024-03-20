#ifndef MAZE_ELEMENT_H
#define MAZE_ELEMENT_H

class MazeElement {
public:
    virtual char getSymbol() const = 0;
    virtual ~MazeElement() {}
};

#endif // MAZE_ELEMENT_H