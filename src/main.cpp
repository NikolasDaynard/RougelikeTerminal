#include <ncurses.h>
#include <iostream>
#include <vector>
#include "helpers.hpp"
#include "entities.hpp"
#include "player.cpp"

int main() {
    initscr();            // Start curses mode
    char input;
    std::vector<Entity *> entities;
    entities.push_back(new Player(10, Tile(1, 1, '0')));
    while (input != 'q') {
        for(Entity *entity : entities) {
            entity->render();
        }
        refresh();            // Print it on the real screen
        input = getch();              // Wait for user input
    }
    endwin();             // End curses mode
    return 0;
}