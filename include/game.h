#pragma once

#include <raylib.h>
#include <iostream>

#include "board.h"
#include "snake.h"
#include "fruit.h"
#include "agent.h"

class Game {
private:
    Board board;
    int cols, rows;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool running;
    bool display_mode;

public:
    Game(const int cols, const int rows, Snake& snake, Fruit& fruit, bool display_mode);

    void draw();
    void update();
    void handle_input();
    void check_collision();
    void run();
};