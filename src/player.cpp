#include "entities.hpp"
#include "helpers.hpp"

class Player : public Entity {
public:
    int facing;

    Player(int health, Tile tile) : Entity(health, tile) {
        blocking = false;
    }

    void render() override {
        // change color here if needed i dunno
        if(facing == LEFT) {
            tile.sprite = '<';
        }else if(facing == RIGHT) {
            tile.sprite = '>';
        }else if(facing == UP) {
            tile.sprite = '^';
        }else if(facing == DOWN) {
            tile.sprite = 'v';
        }
        tile.render();
    }
    std::vector<Entity *> attack(std::vector<Entity *> level) {
        int xDir = 0;
        int yDir = 0;
        if(facing == LEFT) {
            xDir = -1;
        }else if(facing == RIGHT) {
            xDir = 1;
        }else if(facing == UP) {
            yDir = -1;
        }else if(facing == DOWN) {
            yDir = 1;
        }
        if(isTileFree(level, tile.pos.x + xDir, tile.pos.y + yDir)){
            Entity *newTile = new Sword(4, Tile(tile.pos.x + xDir, tile.pos.y + yDir, '#'));
            level.push_back(newTile);
        }
        return level;
    }
};