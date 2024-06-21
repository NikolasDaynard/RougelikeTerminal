#include <ncurses.h>
#include <iostream>
#include <vector>
#include "helpers.hpp"
#include "entities.hpp"

int main() {
    initscr();            // Start curses mode
    char input;
    std::vector<Entity *> entities;
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