#include "snake.h"
#include <iostream>

using namespace std;

Snake::Snake(int cols, int rows, Fruit &fruit) : cols(cols), rows(rows), fruit(fruit) {
    tail_length = 0;
    position.first = cols/2;
    position.second = rows/2;
    direction = Direction::RIGHT;
}

void Snake::draw() {
    DrawRectangle(position.first * 40, position.second * 40, 40, 40, GREEN);
    for (const auto& segment : body) {
        DrawRectangle(segment.first * 40, segment.second * 40, 40, 40, GREEN);
    }
}

void Snake::handle_input() {
    if (IsKeyPressed(KEY_RIGHT) && direction != Direction::LEFT) direction = Direction::RIGHT;
    if (IsKeyPressed(KEY_DOWN) && direction != Direction::UP) direction = Direction::DOWN;
    if (IsKeyPressed(KEY_LEFT) && direction != Direction::RIGHT) direction = Direction::LEFT;
    if (IsKeyPressed(KEY_UP) && direction != Direction::DOWN) direction = Direction::UP;
}

void Snake::update() {
    std::pair<int, int> movement;

    switch (direction) {
        case(Direction::UP): movement.second = -1; break;
        case(Direction::DOWN): movement.second = 1; break;
        case(Direction::LEFT): movement.first = -1; break;
        case(Direction::RIGHT): movement.first = 1; break;
    }

    body.push_front(position);

    position.first += movement.first;
    position.second += movement.second;

    if (body.size() > tail_length) {
        body.pop_back();
    }
}

void Snake::growTail() {
    tail_length++;
}

deque<pair<int, int>> Snake::getBody() {return body;}

pair<int, int> Snake::getPosition() {return position;}

void Snake::update_fitness(bool fruit_eaten) {}

void Snake::reset() {
    tail_length = 0;
    position.first = cols/2;
    position.second = rows/2;
    body.clear();
    direction = Direction::RIGHT;
}