#include "entities.hpp"
#include "helpers.hpp"
#include <vector>

class Sword : public Entity {
public:
    int facing;

    Sword(int health, Tile tile) : Entity(health, tile) {
        blocking = false;
    }

    void render() override {
        // change color here if needed i dunno
        tile.render();
    }
    std::vector<Entity *> update(std::vector<Entity *> level) override {    
        for(Entity *entity : level) {
            if(entity->tile.pos.x == tile.pos.x && entity->tile.pos.y == tile.pos.y) {
                entity->health = entity->health - 1;
            }
        }
        return level;
    }
};