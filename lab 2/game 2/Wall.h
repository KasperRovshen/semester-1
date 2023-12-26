class Wall : public MazeElement {
public:
    char getSymbol() const override {
        return '#';
    }
};
