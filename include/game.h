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
    Snake& snake;
    Fruit fruit;
    int cols, rows;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool running;

public:
    Game(const int cols, const int rows, Snake& snake, Fruit& fruit);

    void draw();
    void update();
    void handle_input();
    void check_collision();
    void run();
};