#include "game.h"

using namespace std;

Game::Game(int cols, int rows, Snake &snake, Fruit &fruit, bool display_mode)
    : running(true), board(cols, rows, snake, fruit), cols(cols), rows(rows), display_mode(display_mode) {
    SCREEN_WIDTH = cols * 40;
    SCREEN_HEIGHT = rows * 40;
    board.reset();
}

void Game::run() {
    if (display_mode) {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SnakeGA");
        SetTargetFPS(10);

        while(!board.getGameOver() && !WindowShouldClose()) {
            handle_input();
            update();
            check_collision();
            draw();
        }
        CloseWindow();
    } else {
        int max_steps = 10000;
        int steps = 0;
        while(!board.getGameOver() && steps < max_steps) {
            handle_input();
            update();
            check_collision();
            steps++;
        }
    }
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
