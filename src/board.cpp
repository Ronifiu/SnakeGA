#include "board.h"

using namespace std;

Board::Board(int cols, int rows, Snake& snake, Fruit& fruit) : cols(cols), rows(rows), fruit(fruit), snake(snake) {
    CELLWIDTH = 40;
    gameOver = false;
    grid = vector<vector<CellType>>(cols, vector<CellType>(rows, CellType::EMPTY));
    placeFruit();
}

void Board::draw() {
    for (int i = 0; i < cols; i++) {
        DrawLine(i*CELLWIDTH, 0, i*CELLWIDTH, rows*CELLWIDTH, GRAY);
    }
    for (int i = 0; i < rows; i++) {
        DrawLine(0, i*CELLWIDTH, cols*CELLWIDTH, i*CELLWIDTH, GRAY);
    }
    fruit.draw();
    snake.draw();
}

void Board::handle_input() {
    snake.handle_input();
}

void Board::update() {
    if (gameOver) {
        reset();
        return;
    }
    updateGrid();
    bool fruit_eaten = snake.getPosition() == fruit.getPosition();
    if (fruit_eaten) {
        placeFruit();
        snake.growTail();
    }
    snake.update();
    snake.update_fitness(fruit_eaten);
}

void Board::updateGrid() {
    deque<pair<int, int>> snake_body = snake.getBody();
    pair<int, int> snake_head = snake.getPosition();
    pair<int, int> fruit_pos = fruit.getPosition();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (grid[i][j] != CellType::FRUIT) grid[i][j] = CellType::EMPTY;
        }
    }
    for (const auto& segment : snake_body) {
        grid[segment.first][segment.second] = CellType::SNAKE;
    }
    grid[snake_head.first][snake_head.second] = CellType::HEAD;
}

void Board::placeFruit() {
    pair<int, int> fruit_pos;
    do {
        fruit.getRandomPosition();
        fruit_pos = fruit.getPosition();
    } while(grid[fruit_pos.first][fruit_pos.second] != CellType::EMPTY);
    
    grid[fruit_pos.first][fruit_pos.second] = CellType::FRUIT;
}

void Board::check_collision() {
    pair<int, int> snake_head = snake.getPosition();
    deque<pair<int, int>> snake_body = snake.getBody();
    if (snake_head.first < 0 || snake_head.first >= cols || snake_head.second < 0 || snake_head.second >= rows) {
        gameOver = true;
    }
    for (const auto& segment : snake_body) {
        if (segment.first == snake_head.first && segment.second == snake_head.second) {
            gameOver = true;
        }
    }
}

void Board::reset() {
    grid = vector<vector<CellType>>(cols, vector<CellType>(rows, CellType::EMPTY));
    placeFruit();
    snake.reset();
    gameOver = false;
}