#include "agent.h"
#include <iostream>

using namespace std;

Agent::Agent(int cols, int rows, Fruit fruit, int input_size, int hidden_size, int output_size)
    : Snake(cols, rows, fruit), nn(input_size, hidden_size, output_size) {
        previous_distance_to_fruit = abs(position.first - fruit.getPosition().first) + 
                                 abs(position.second - fruit.getPosition().second);
    }

void Agent::handle_input() {
    vector<double> inputs = get_inputs();
    vector<double> outputs = nn.forward(inputs);

    vector<pair<int, Direction>> valid_moves;
    for (int i = 0; i < 4; i++) {
        Direction potential_dir = static_cast<Direction>(i);
        pair<int, int> next_pos = get_next_position(potential_dir);
        
        if (!is_obstacle(next_pos.first, next_pos.second)) {
            valid_moves.push_back({outputs[i], potential_dir});
        }
    }

    if (!valid_moves.empty()) {
        auto best_move = max_element(valid_moves.begin(), valid_moves.end());
        direction = best_move->second;
    }
}


void Agent::update_fitness(bool fruit_eaten) {
    int new_distance = abs(position.first - fruit.getPosition().first) + 
                       abs(position.second - fruit.getPosition().second);

    if (new_distance < previous_distance_to_fruit) {
        fitness += 2;  // Reward for moving towards the fruit
    } else {
        fitness -= 2;  // Penalize for moving away
    }

    if (fruit_eaten) {
        fitness += 100;  // Large reward for eating fruit
    }

    previous_distance_to_fruit = new_distance;
}


vector<double> Agent::get_inputs() {
    vector<double> distance_to_fruit = dist_fruit();
    vector<double> distance_to_wall = dist_wall();
    vector<double> distance_to_body = dist_body();

    return {
        distance_to_fruit[0], distance_to_wall[0], distance_to_body[0],
        distance_to_fruit[1], distance_to_wall[1], distance_to_body[1],
        distance_to_fruit[2], distance_to_wall[2], distance_to_body[2],
        distance_to_fruit[3], distance_to_wall[3], distance_to_body[3],
        distance_to_fruit[4], distance_to_wall[4], distance_to_body[4],
        distance_to_fruit[5], distance_to_wall[5], distance_to_body[5],
        distance_to_fruit[6], distance_to_wall[6], distance_to_body[6],
        distance_to_fruit[7], distance_to_wall[7], distance_to_body[7]
    };
}

vector<double> Agent::dist_fruit() {
    pair<int, int> fruit_pos = fruit.getPosition();
    vector<double> distance_to_fruit(8, 1.0);

    int dx = fruit_pos.first - position.first;
    int dy = fruit_pos.second - position.second;
    
    int rel_x, rel_y;

    switch (direction) {
        case Direction::RIGHT: rel_x = dx; rel_y = dy; break;
        case Direction::LEFT:  rel_x = -dx; rel_y = -dy; break;
        case Direction::UP:    rel_x = dy; rel_y = -dx; break;
        case Direction::DOWN:  rel_x = -dy; rel_y = dx; break;
    }

    double norm_dist = sqrt(rel_x * rel_x + rel_y * rel_y) / max(cols, rows);

    if (rel_x > 0 && rel_y == 0) distance_to_fruit[0] = rel_x / (double)cols; // Forward
    if (rel_x > 0 && rel_y < 0) distance_to_fruit[1] = norm_dist; // Forward-right
    if (rel_x == 0 && rel_y < 0) distance_to_fruit[2] = abs(rel_y) / (double)rows; // Right
    if (rel_x < 0 && rel_y < 0) distance_to_fruit[3] = norm_dist; // Backward-right
    if (rel_x == 0 && rel_y > 0) distance_to_fruit[4] = rel_y / (double)rows; // Backward
    if (rel_x < 0 && rel_y > 0) distance_to_fruit[5] = norm_dist; // Backward-left 
    if (rel_x < 0 && rel_y == 0) distance_to_fruit[6] = abs(rel_x) / (double)cols; // Left
    if (rel_x > 0 && rel_y > 0) distance_to_fruit[7] = norm_dist; // Forward-left
    
    return distance_to_fruit;
}

vector<double> Agent::dist_wall() {
    vector<double> distance_to_wall(8, 1.0);

    int left_dist   = position.first;         // Distance to left wall
    int right_dist  = cols - position.first - 1;  // Distance to right wall
    int up_dist     = position.second;        // Distance to top wall
    int down_dist   = rows - position.second - 1; // Distance to bottom wall

    // Convert to relative distances based on direction
    switch (direction) {
        case Direction::RIGHT:
            distance_to_wall[0] = right_dist / (double)cols; // Forward
            distance_to_wall[2] = down_dist / (double)rows; // Right
            distance_to_wall[4] = left_dist / (double)cols; // Backward
            distance_to_wall[6] = up_dist / (double)rows; // Left
            break;

        case Direction::LEFT:
            distance_to_wall[0] = left_dist / (double)cols; // Forward
            distance_to_wall[2] = up_dist / (double)rows; // Right
            distance_to_wall[4] = right_dist / (double)cols; // Backward
            distance_to_wall[6] = down_dist / (double)rows; // Left
            break;

        case Direction::UP:
            distance_to_wall[0] = up_dist / (double)rows; // Forward
            distance_to_wall[2] = right_dist / (double)cols; // Right
            distance_to_wall[4] = down_dist / (double)rows; // Backward
            distance_to_wall[6] = left_dist / (double)cols; // Left
            break;

        case Direction::DOWN:
            distance_to_wall[0] = down_dist / (double)rows; // Forward
            distance_to_wall[2] = left_dist / (double)cols; // Right
            distance_to_wall[4] = up_dist / (double)rows; // Backward
            distance_to_wall[6] = right_dist / (double)cols; // Left
            break;
    }

    // Diagonal distances (Pythagoras theorem)
    distance_to_wall[1] = sqrt(distance_to_wall[0] * distance_to_wall[0] +
                               distance_to_wall[2] * distance_to_wall[2]); // Forward-right

    distance_to_wall[3] = sqrt(distance_to_wall[2] * distance_to_wall[2] +
                               distance_to_wall[4] * distance_to_wall[4]); // Backward-right

    distance_to_wall[5] = sqrt(distance_to_wall[4] * distance_to_wall[4] +
                               distance_to_wall[6] * distance_to_wall[6]); // Backward-left

    distance_to_wall[7] = sqrt(distance_to_wall[6] * distance_to_wall[6] +
                               distance_to_wall[0] * distance_to_wall[0]); // Forward-left

    return distance_to_wall;
}

vector<double> Agent::dist_body() {
    vector<double> distance_to_body(8, 1.0);

    for (auto& segment : body) {
        int dx = segment.first - position.first;
        int dy = segment.second - position.second;

        int rel_x, rel_y;

        switch (direction) {
            case Direction::RIGHT: rel_x = dx; rel_y = dy; break;
            case Direction::LEFT:  rel_x = -dx; rel_y = -dy; break;
            case Direction::UP:    rel_x = dy; rel_y = -dx; break;
            case Direction::DOWN:  rel_x = -dy; rel_y = dx; break;
        }

        double norm_dist = sqrt(rel_x * rel_x + rel_y * rel_y) / max(rows, cols);

        if (rel_x > 0 && rel_y == 0) distance_to_body[0] = min(distance_to_body[0], rel_x / (double)cols); // Forward
        if (rel_x > 0 && rel_y < 0) distance_to_body[1] = min(distance_to_body[1], norm_dist); // Forward-right
        if (rel_x == 0 && rel_y < 0) distance_to_body[2] = min(distance_to_body[2], abs(rel_y) / (double)rows); // Right
        if (rel_x < 0 && rel_y < 0) distance_to_body[3] = min(distance_to_body[3], norm_dist); // Backward-right
        if (rel_x == 0 && rel_y > 0) distance_to_body[4] = min(distance_to_body[4], rel_y / (double)rows); // Backward
        if (rel_x < 0 && rel_y > 0) distance_to_body[5] = min(distance_to_body[5], norm_dist); // Backward-left
        if (rel_x < 0 && rel_y == 0) distance_to_body[6] = min(distance_to_body[6], abs(rel_x) / (double)cols); // Left
        if (rel_x > 0 && rel_y > 0) distance_to_body[7] = min(distance_to_body[7], norm_dist); // Forward-left
    }

    return distance_to_body;
}



double Agent::distance_to_obstacle(int x, int y, int dx, int dy) {
    double distance = 0.0;
    while (x >= 0 && x < cols && y >= 0 && y < rows && !is_obstacle(x, y)) {
        x += dx;
        y += dy;
        distance += 1.0;
    }
    return distance / max(cols, rows);  // Normalize
}

double Agent::is_obstacle(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows) return 1.0; // Wall collision
    for (auto& segment : body) {
        if (segment.first == x && segment.second == y) return 1.0; // Body collision
    }
    return 0.0;
}

void Agent::reset() {
    tail_length = 2;
    position.first = rand() % cols;
    position.second = rand() % rows;
    direction = Direction::RIGHT;
    body.clear();
    fitness = 0.0;
    previous_distance_to_fruit = abs(position.first - fruit.getPosition().first) + 
                                 abs(position.second - fruit.getPosition().second);
}


void Agent::terminate() {
    fitness -= fitness * 0.2;
}

pair<int, int> Agent::get_next_position(Direction direction) {
    pair<int, int> next_position = position;

    switch (direction) {
        case Direction::RIGHT: next_position.first += 1; break;
        case Direction::LEFT:  next_position.first -= 1; break;
        case Direction::UP:    next_position.second -= 1; break;
        case Direction::DOWN:  next_position.second += 1; break;
    }

    return next_position;
}