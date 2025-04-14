#pragma once

#include "game.h"
#include "genetic.h"

class Simulation {
private:
    int cols, rows;
    int population_size;
    int input_size, hidden_size, output_size;
public:
    Simulation(int cols, int rows, int population_size, int input_size, int hidden_size, int output_size);

    void run(int max_gen);
};