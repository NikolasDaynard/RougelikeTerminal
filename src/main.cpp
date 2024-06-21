#include <ncurses.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "helpers.hpp"
#include "entities.hpp"
#include "player.cpp"
#include "level.cpp"

int main() {
    srand(time(NULL));
    initscr();            // Start curses mode
    curs_set(0); // hide cursor
    start_color();
    cbreak();// Disable line buffering
    noecho(); // Prevent user input from being echoed to the screen
    nodelay(stdscr, TRUE); // causes input to be non-blocking
    keypad(stdscr, TRUE); // Capture special keys like arrow keys
    int input;
    std::vector<Entity *> entities;
    Player *player = new Player(10, Tile(1, 1, '0'));
    
    for(Entity *entity : createLevel()) {
        entities.push_back(entity);
    }
    // make sure player is ontop of the stack
    entities.push_back(player);

    while (input != 'q' && input != 27) {
        clear();
        for(Entity *entity : entities) {
            entity->render();
        }
        refresh();            // Print it on the real screen
        input = getch();              // Wait for user input
        switch (input) {
            case KEY_UP:
            case 'w':
                player->tile.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                player->tile.pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
                player->tile.pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
                player->tile.pos.x += 1;
                break;
            default:
                Tile(4, 4, input).render();
                break;
        }
    }
    endwin();             // End curses mode
    delete player;
    return 0;
}