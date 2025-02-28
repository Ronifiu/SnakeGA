#include "game.h"

using namespace std;

Game::Game(int cols, int rows, Snake &snake, Fruit &fruit)
    : running(true), board(cols, rows, snake, fruit), cols(cols), rows(rows), snake(snake), fruit(fruit) {
    SCREEN_WIDTH = cols * 40;
    SCREEN_HEIGHT = rows * 40;
}

void Game::run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SnakeGA");
    SetTargetFPS(10);

    while(!WindowShouldClose()) {
        handle_input();
        update();
        check_collision();
        draw();
    }
    CloseWindow();
}

void Game::draw() {
    BeginDrawing();

    ClearBackground(BLACK);
    board.draw();

    EndDrawing();
}

void Game::handle_input() {
    board.handle_input();
}

void Game::update() {
    board.update();
}

void Game::check_collision() {
    board.check_collision();
}
