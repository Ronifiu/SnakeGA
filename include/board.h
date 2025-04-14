#pragma once

#include <raylib.h>
#include <utility>
#include <vector>

#include "snake.h"
#include "fruit.h"

enum class CellType {EMPTY, SNAKE, FRUIT, HEAD};

class Board {
private:
    Snake& snake;
    Fruit fruit;
    std::vector<std::vector<CellType>> grid;
    bool gameOver;
    int steps;
    int steps_without_eating = 400;
public:
    int cols, rows;
    int CELLWIDTH;

    Board(const int cols, const int rows, Snake& snake, Fruit& fruit);

    void draw();
    void update();
    void handle_input();
    void check_collision();
    void updateGrid();
    void placeFruit();
    void reset();
    bool getGameOver();
};