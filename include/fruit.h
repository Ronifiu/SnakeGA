#pragma once

#include <raylib.h>
#include <iostream>
#include <utility>
#include <cstdlib>

class Fruit {
private:
    std::pair<int, int> position;
    int cols, rows;
    int radius;
    int CELLWIDTH;
public:
    bool eaten;

    Fruit(int cols, int rows);

    void draw();
    void update();
    std::pair<int, int> getPosition();
    void getRandomPosition();
};