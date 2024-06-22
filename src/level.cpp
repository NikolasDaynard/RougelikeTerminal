#include <vector>
#include <ncurses.h>
#include "helpers.hpp"
#include "entities.hpp"

class Wall : public Entity {
public:
    Wall(Tile tile) : Entity(1000000000, tile) {}

    void render() const override {
        // change color here if needed
        tile.render();
    }
};
std::vector<Entity *> addRectangle(std::vector<Entity *> level, int rectx, int recty, int rectw, int recth) {
    for(int x = 0; x < COLS; x++) {
        for(int y = 0; y < LINES; y++) {
            if((x == rectx && y >= recty - recth && y <= recty) || // left bar
                (x == rectx + rectw && y >= recty - recth && y <= recty) || // right bar
                (y == recty && x >= rectx && x <= rectx + rectw) || // bottom bar
                (y == recty - recth && x >= rectx && x <= rectx + rectw) // top bar
                ) {
                level.push_back(new Wall(Tile(x, y, '+')));
            }
        }
    }
    return level;
}
std::vector<Entity *> levelGen() {
    std::vector<Entity *> level;
    return level;
}
std::vector<Entity *> createLevel(Point currentLevel) {
    std::vector<Entity *> level;
    // for(int x = 0; x < COLS; x++) {
    //     for(int y = 0; y < LINES; y++) {
    //         level.push_back(new Wall(Tile(x, y, '+')));
    //     }
    // }
    if(currentLevel == Point(0, 0)) { // starting level
        level = addRectangle(level, 10, 10, 5, 5);
        // for(int x = 0; x < COLS; x++) {
        //     for(int y = 0; y < LINES; y++) {
        //         level.push_back(new Wall(Tile(x, y, ' ')));
        //     }
        // }
    }

    return level;
}