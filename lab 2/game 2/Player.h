class Player : public MazeElement {
public:
    char getSymbol() const override {
        return 'P';
    }
};