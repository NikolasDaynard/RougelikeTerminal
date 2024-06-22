#ifndef ENTITIES_HPP
#define ENTITIES_HPP
class Entity {
private:
    int health;

public:
    bool blocking = true;
    Tile tile;
    Entity(int health, Tile tile) : health(health), tile(tile) {}
    Entity(int health, bool blocking, Tile tile) : health(health), blocking(blocking), tile(tile) {}
    virtual void render() const {}
};
#endif