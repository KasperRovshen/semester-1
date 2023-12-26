class Treasure : public MazeElement {
public:
    char getSymbol() const override {
        return 'T';
    }
};