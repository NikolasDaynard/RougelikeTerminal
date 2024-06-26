#include <ncurses.h>
#define COLS COLS / 2
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "helpers.hpp"
#include "entities.hpp"
#include "swordWeapon.cpp"
#include "player.cpp"
#include "level.cpp"
#include "time.cpp"


int main() {
    srand(time(NULL));
    initscr();            // Start curses mode
    curs_set(0); // hide cursor
    start_color();
    cbreak();// Disable line buffering
    noecho(); // Prevent user input from being echoed to the screen
    keypad(stdscr, TRUE); // Capture special keys like arrow keys
    int input = 0;
    int inputTemp;
    Point previousPlayerPosition = Point(100, 100);
    
    std::vector<Entity *> entities;
    Timer playerMovementTimer = Timer();
    Timer inputTimer = Timer();
    Timer gameMaxClock = Timer();
    Player *player = new Player(10, Tile(1, 1, '0'));

    Point currentLevel = Point(0, 0);
    for(Entity *entity : createLevel(currentLevel)) {
        entities.push_back(entity);
    }
    // make sure player is ontop of the stack
    entities.push_back(player);
    nodelay(stdscr, TRUE); // causes input to be non-blocking

    while (input != 'q' && input != 27) {
        clear();
        for(Entity *entity : entities) {
            entity->render();
        }
        refresh();            // Print it on the real screen

        inputTemp = getch();
        if(inputTemp != ERR) {  // only update input if it exists
            input = inputTemp;
            inputTimer.resetTimer();
        }else{
            // if enough time has elapsed, assume key was lifted
            if(inputTimer.readTimer() > 70) {
                input = inputTemp;
                inputTimer.resetTimer();
            }
        }
        previousPlayerPosition = player->tile.pos;
        if(playerMovementTimer.readTimer() > 100) {
            switch (input) {
                case KEY_UP:
                case 'w':
                    player->tile.pos.y -= 1;
                    player->facing = UP;
                    playerMovementTimer.resetTimer();
                    break;
                case KEY_DOWN:
                case 's':
                    player->tile.pos.y += 1;
                    player->facing = DOWN;
                    playerMovementTimer.resetTimer();
                    break;
                case KEY_LEFT:
                case 'a':
                    player->tile.pos.x -= 1;
                    player->facing = LEFT;
                    playerMovementTimer.resetTimer();
                    break;
                case KEY_RIGHT:
                case 'd':
                    player->tile.pos.x += 1;
                    player->facing = RIGHT;
                    playerMovementTimer.resetTimer();
                    break;
                case ' ': // sapce
                    entities = player->attack(entities);
                    break;
                default:
                    Tile(4, 4, input).render();
                    break;
            }
        }
        // bounce if tile is occupied + update entities
        for(Entity *entity : entities) {
            entities = entity->update(entities);
            if(entity->tile.pos.x == player->tile.pos.x && entity->tile.pos.y == player->tile.pos.y && entity->blocking) {
                player->tile.pos = previousPlayerPosition;
            }
        }
        entities.erase(
            std::remove_if(entities.begin(), entities.end(), [](Entity *entity) {
                if (entity->health <= 0) {
                    delete entity;
                    return true;
                }
                return false;
            }),
            entities.end()
        );
        while(gameMaxClock.readTimer() < 16) {
            //wait 16.6 ms to reduce flicker
        }
        gameMaxClock.resetTimer();
    }
    endwin();             // End curses mode
    delete player;
    return 0;
}