#include "entities.hpp";
#include "helpers.hpp"

class Player : public Entity {
    Player(int health, Tile tile) : Entity(health, tile) {}

    void render() const override {
        // change color here if needed
        tile.render();
    }
};