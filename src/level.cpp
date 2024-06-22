#include <vector>
#include <ncurses.h>
#include "helpers.hpp"
#include "entities.hpp"
#include <stdlib.h>

enum direction {
    LEFT, UP, DOWN, RIGHT, NONE
};

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
bool isRectFree(std::vector<Entity *> level, int rectx, int recty, int rectw, int recth) {
    for(Entity *wall : level){
        if((wall->tile.pos.x == rectx && wall->tile.pos.y >= recty && wall->tile.pos.y <= recty + recth) || // left bar
            (wall->tile.pos.x == rectx + rectw && wall->tile.pos.y >= recty && wall->tile.pos.y <= recty + recth) || // right bar
            (wall->tile.pos.y == recty && wall->tile.pos.x >= rectx && wall->tile.pos.x <= rectx + rectw) || // bottom bar
            (wall->tile.pos.y == recty + recth && wall->tile.pos.x >= rectx && wall->tile.pos.x <= rectx + rectw) // top bar
            ) {

            return false;
        }
    }
    return true;
}

int findOpenDirection(std::vector<Entity *> level, int x, int y) {
    bool left = true;
    bool right = true;
    bool down = true;
    bool up = true;
    for(Entity *wall : level){
        // handles right
        if((x + 1 == wall->tile.pos.x && y + 1 == wall->tile.pos.y) ||
            (x + 1 == wall->tile.pos.x && y - 1 == wall->tile.pos.y) ||
            x + 1 == wall->tile.pos.x && y == wall->tile.pos.y) {
            right = false;
        }
    }
    if(right) {
        return RIGHT;
    }else {
        return NONE;
    }
}

std::vector<Entity *> iterateLevel(std::vector<Entity *> level) {
    int walls = level.size();
    if (walls == 0) {
        return level; // Return unchanged if level is empty
    }

    int doorWall = rand() % walls;
    int openDirection = NONE;

    // Check if the randomly chosen entity is not a door ('O') and erase it if not
    if (level[doorWall]->tile.sprite != 'O') {
        // try and make a room
        // start with the []=[] connection part, check what direction that is free
        // if there is one free, make a rectangle, and delete the overalpping square
        if(findOpenDirection(level, level[doorWall]->tile.pos.x, level[doorWall]->tile.pos.y) == RIGHT) {
            level = addRectangle(level, level[doorWall]->tile.pos.x, level[doorWall]->tile.pos.y - 1, 3, 3);
            Point pointToErase = level[doorWall]->tile.pos;
            level.erase(level.begin() + doorWall);
            int i = 0;
            for(Entity *wall : level){
                if(wall->tile.pos.x == pointToErase.x && wall->tile.pos.y == pointToErase.y) {
                    level.erase(level.begin() + i);
                }
                i++;
            }
        }
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
        for(int i = 0; i < 1; i++) {
            level = iterateLevel(level);
        }
    }

    return level;
}