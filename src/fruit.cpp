#include "fruit.h"

Fruit::Fruit(int cols, int rows) : cols(cols), rows(rows) {
    radius = 15;
    eaten = false;
    CELLWIDTH = 40;
    getRandomPosition();
}

void Fruit::getRandomPosition() {
    position.first = rand() % cols;
    position.second = rand() % rows;
}

void Fruit::draw() {
    DrawCircle(position.first * CELLWIDTH + CELLWIDTH/2, position.second * CELLWIDTH + CELLWIDTH/2, radius, RED);
}

std::pair<int, int> Fruit::getPosition() {
    return position;
}

