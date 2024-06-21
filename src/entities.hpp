#ifndef ENTITIES_HPP
#define ENTITIES_HPP
class Entity {
private:
    int health;

public:
    Tile tile;
    Entity(int health, Tile tile) : health(health), tile(tile) {}
    virtual void render() const {}
};
#endif