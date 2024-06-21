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
std::vector<Entity *> createLevel() {
    std::vector<Entity *> level;
    for(int x = 0; x < COLS; x++) {
        for(int y = 0; y < LINES; y++) {
            level.push_back(new Wall(Tile(x, y, '+')));
        }
    }

    return level;
}