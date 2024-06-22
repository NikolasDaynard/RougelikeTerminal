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
    if(rectw < 0) {
        rectx += rectw; 
        rectw = abs(rectw);
    }
    if(recth < 0) {
        recty += recth; 
        recth = abs(recth);
    }

    for(int x = 0; x < COLS; x++) {
        for(int y = 0; y < LINES; y++) {
            if((x == rectx && y >= recty && y <= recty + recth) || // left bar
                (x == rectx + rectw && y >= recty && y <= recty + recth) || // right bar
                (y == recty && x >= rectx && x <= rectx + rectw) || // bottom bar
                (y == recty + recth && x >= rectx && x <= rectx + rectw) // top bar
                ) {

                level.push_back(new Wall(Tile(x, y, '+')));
            }
            if(x >= rectx && x <= rectx + rectw && 
                y >= recty && y <= recty + recth) {
                    // make invis tile for gen
                    Wall *newTile = new Wall(Tile(x, y, ' '));
                    newTile->blocking = false;
                    level.push_back(newTile);
                }
        }
    }
    return level;
}
bool isRectFree(std::vector<Entity *> level, int rectx, int recty, int rectw, int recth) {
    if(rectw < 0) {
        rectx += rectw; 
        rectw = abs(rectw);
    }
    if(recth < 0) {
        recty += recth; 
        recth = abs(recth);
    }

    if(rectx < 0 || rectx > COLS - 1 || recty < 0 || recty > LINES - 1) {
        return false;
    }

    for(Entity *wall : level){
        if(((wall->tile.pos.x == rectx && wall->tile.pos.y >= recty && wall->tile.pos.y <= recty + recth) || // left bar
            (wall->tile.pos.x == rectx + rectw && wall->tile.pos.y >= recty && wall->tile.pos.y <= recty + recth) || // right bar
            (wall->tile.pos.y == recty && wall->tile.pos.x >= rectx && wall->tile.pos.x <= rectx + rectw) || // bottom bar
            (wall->tile.pos.y == recty + recth && wall->tile.pos.x >= rectx && wall->tile.pos.x <= rectx + rectw) // top bar
            ) && wall->tile.sprite == ' ') {

            return false;
        }
    }
    return true;
}

bool isTileFree(std::vector<Entity *> level, int x, int y) {
    if(x < 0 || x > COLS - 1 || y < 0 || y > LINES - 1) {
        return false;
    }
    for(Entity *wall : level){
        if(wall->tile.pos.x == x && wall->tile.pos.y == y && wall->blocking) {
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
    if(!isRectFree(level, x + 1, y - 1, 3, 3) ||
        !isTileFree(level, x - 1, y)) {
        right = false;
    }
    if(!isRectFree(level, x - 1, y - 1, -3, 3) ||
        !isTileFree(level, x + 1, y)) {
        left = false;
    }
    if(!isRectFree(level, x - 1, y - 1, 3, -3) ||
        !isTileFree(level, x, y + 1)) {
        up = false;
    }
    if(!isRectFree(level, x - 1, y + 1, 3, 3) ||
        !isTileFree(level, x, y - 1)) {
        down = false;
    }
    if(right) {
        return RIGHT;
    }else if(left) {
        return LEFT;
    }else if(up) {
        return UP;
    }else if(down) {
        return DOWN;
    }else{
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
        openDirection = findOpenDirection(level, level[doorWall]->tile.pos.x, level[doorWall]->tile.pos.y);
        Point pointToErase = Point(-1, -1);
        if(openDirection == RIGHT) {
            level = addRectangle(level, level[doorWall]->tile.pos.x, level[doorWall]->tile.pos.y - 1, 3, 3);
        }else if(openDirection == LEFT) {
            level = addRectangle(level, level[doorWall]->tile.pos.x, level[doorWall]->tile.pos.y - 1, -3, 3);
        }else if(openDirection == DOWN) {
            level = addRectangle(level, level[doorWall]->tile.pos.x - 1, level[doorWall]->tile.pos.y, 3, 3);
        }else if(openDirection == UP){
            level = addRectangle(level, level[doorWall]->tile.pos.x - 1, level[doorWall]->tile.pos.y, 3, -3);
        }
        if(openDirection != NONE) {
            pointToErase = level[doorWall]->tile.pos;
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
        for(int i = 0; i < 1100; i++) {
            level = iterateLevel(level);
        }
    }

    return level;
}