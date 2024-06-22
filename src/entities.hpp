#ifndef ENTITIES_HPP
#define ENTITIES_HPP
class Entity {
private:

public:
    int health;
    bool blocking = true;
    Tile tile;
    Entity(int health, Tile tile) : health(health), tile(tile) {}
    Entity(int health, bool blocking, Tile tile) : health(health), blocking(blocking), tile(tile) {}
    virtual void render() {}
    virtual std::vector<Entity *> update(std::vector<Entity *> level) {
        return level;
    }
};
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
#endif