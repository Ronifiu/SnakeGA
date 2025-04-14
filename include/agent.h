#pragma once

#include "snake.h"
#include "neural.h"

class Agent : public Snake {
private:
    std::pair<int, int> get_next_position(Direction direction);
public:
    NeuralNetwork nn;
    double fitness = 0.0;
    double previous_distance_to_fruit;

    Agent(int cols, int rows, Fruit fruit, int input_size, int hidden_size, int output_size);

    void handle_input() override;
    void update_fitness(bool fruit_eaten) override;
    std::vector<double> get_inputs();
    double is_obstacle(int x, int y);
    double distance_to_obstacle(int x, int y, int dx, int dy);
    void reset() override;
    void terminate() override;
    std::vector<double> dist_fruit();
    std::vector<double> dist_wall();
    std::vector<double> dist_body();
};