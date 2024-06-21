#ifndef HELPERS_HPP
#define HELPERS_HPP
class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    int x, y;
};

class Tile {
public:
    Point pos;
    char sprite;
    Tile(Point pos, char sprite) : pos(pos), sprite(sprite) {}
    Tile(int x, int y, char sprite) : pos(Point(x, y)), sprite(sprite) {}
    void render() const {
        mvaddch(pos.y, pos.x, sprite);
    };
};
#endif