#pragma once

#include <raylib.h>
#include <iostream>

#include "board.h"

class Game {
private:
    Board board;
    int cols, rows;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool running;

public:

    Game(const int cols, const int rows);
    void draw();
    void update();
    void handle_input();
    void check_collision();
    void run();
};