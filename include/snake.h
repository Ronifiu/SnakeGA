#pragma once

#include <raylib.h>
#include <utility>
#include <cstdlib>
#include <vector>
#include <deque>

#include "fruit.h"

enum class Direction {UP, DOWN, LEFT, RIGHT};

class Snake {
protected:
    Fruit &fruit;
    int cols, rows;
    int tail_length;
    std::pair<int, int> position;
    std::deque<std::pair<int, int>> body;
    Direction direction;
public:
    Snake(int cols, int rows, Fruit &fruit);

    void draw();
    virtual void update();
    virtual void handle_input();
    virtual void update_fitness(bool fruit_eaten);
    void growTail();
    virtual void reset();
    std::deque<std::pair<int, int>> getBody();
    std::pair<int, int> getPosition();
};