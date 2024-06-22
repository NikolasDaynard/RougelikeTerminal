#include <vector>
#include <ncurses.h>
#include "helpers.hpp"
#include "entities.hpp"
#include <stdlib.h>

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
            if((x == rectx && y >= recty && y <= recty + recth) || // left bar
                (x == rectx + rectw && y >= recty && y <= recty + recth) || // right bar
                (y == recty && x >= rectx && x <= rectx + rectw) || // bottom bar
                (y == recty + recth && x >= rectx && x <= rectx + rectw) // top bar
                ) {

                level.push_back(new Wall(Tile(x, y, '+')));
            }
        }
    }
    return level;
}
std::vector<Entity*> iterateLevel(std::vector<Entity *> level) {
    int walls = level.size();
    if (walls == 0) {
        return level; // Return unchanged if level is empty
    }

    int doorWall = rand() % walls;

    // Check if the randomly chosen entity is not a door ('O') and erase it if not
    if (level[doorWall]->tile.sprite != 'O') {
        level.erase(level.begin() + doorWall);
    }

    return level; // Return modified or unchanged level vector
}
std::vector<Entity *> createLevel(Point currentLevel) {
    std::vector<Entity *> level;
    // for(int x = 0; x < COLS; x++) {
    //     for(int y = 0; y < LINES; y++) {
    //         level.push_back(new Wall(Tile(x, y, '+')));
    //     }
    // }
    if(currentLevel == Point(0, 0)) { // starting level
        level = addRectangle(level, 0, 0, 5, 5);
        // for(int x = 0; x < COLS; x++) {
        //     for(int y = 0; y < LINES; y++) {
        //         level.push_back(new Wall(Tile(x, y, ' ')));
        //     }
        // }
        for(int i = 0; i < 10; i++) {
            level = iterateLevel(level);
        }
    }

    return level;
}