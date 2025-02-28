#pragma once

#include "snake.h"
#include "neural.h"

class Agent : public Snake {
public:
    NeuralNetwork nn;
    double fitness = 0.0;

    Agent(int cols, int rows, Fruit &fruit, int input_site, int hidden_size, int output_size);

    void handle_input() override;
    void update_fitness(bool fruit_eaten) override;
    std::vector<double> get_inputs();
    double is_obstacle(int x, int y);
    void reset() override;
};