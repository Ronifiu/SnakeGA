#pragma once

#include <raylib.h>
#include <utility>
#include <cstdlib>
#include <vector>
#include <deque>

enum class Direction {UP, DOWN, LEFT, RIGHT};

class Snake {
private:
    std::pair<int, int> position;
    std::deque<std::pair<int, int>> body;
    int cols, rows;
    Direction direction;
    int tail_length;
public:
    Snake(int cols, int rows);

    void draw();
    void update();
    void handle_input();
    void growTail();
    std::deque<std::pair<int, int>> getBody();
    std::pair<int, int> getPosition();
};