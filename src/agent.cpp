#include "agent.h"
#include <iostream>

using namespace std;

Agent::Agent(int cols, int rows, Fruit &fruit, int input_size, int hidden_size, int output_size)
    : Snake(cols, rows, fruit), nn(input_size, hidden_size, output_size) {}

void Agent::handle_input() {
    vector<double> inputs = get_inputs();
    vector<double> outputs = nn.forward(inputs);

    int max_index = distance(outputs.begin(), max_element(outputs.begin(), outputs.end()));
    cout << max_index <<endl; 

    switch (max_index) {
        case 0: if (direction != Direction::LEFT) direction = Direction::RIGHT; break;
        case 1: if (direction != Direction::UP) direction = Direction::DOWN; break;
        case 2: if (direction != Direction::RIGHT) direction = Direction::LEFT; break;
        case 3: if (direction != Direction::DOWN) direction = Direction::UP; break;
    }
}

void Agent::update_fitness(bool fruit_eaten) {
    if (fruit_eaten) fitness += 10;
    fitness += 0.1;
}

vector<double> Agent::get_inputs() {
    pair<int, int> fruit_pos = fruit.getPosition();
    return {
        position.first / (double)cols,
        position.second / (double)rows,
        1 - (position.first / (double)cols),
        1 - (position.first / (double)rows),

        (fruit_pos.first / (double)cols) - (position.first / (double)cols),
        (fruit_pos.second / (double)rows) - (position.second / (double)rows), 

        direction == Direction::RIGHT ? 1.0 : 0.0,
        direction == Direction::LEFT ? 1.0 : 0.0,
        direction == Direction::UP ? 1.0 : 0.0,
        direction == Direction::DOWN ? 1.0 : 0.0,

        is_obstacle(position.first + 1, position.second),  // Right
        is_obstacle(position.first - 1, position.second),  // Left
        is_obstacle(position.first, position.second - 1),  // Up
        is_obstacle(position.first, position.second + 1),  // Down
    };
}

double Agent::is_obstacle(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows) return 1.0; // Wall collision
    for (auto& segment : body) {
        if (segment.first == x && segment.second == y) return 1.0; // Body collision
    }
    return 0.0;
}

void Agent::reset() {
    tail_length = 0;
    position.first = cols/2;
    position.second = rows/2;
    direction = Direction::RIGHT;
    body.clear();
    NeuralNetwork new_nn(14, 28, 4);
    nn = new_nn;
}
