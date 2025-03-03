#pragma once

#include <vector>

#include "agent.h"
#include "fruit.h"

class GeneticAlgorithm {
public:
    std::vector<Agent> population;
    Fruit& fruit;
    int population_size;
    int cols, rows;

    GeneticAlgorithm(int cols, int rows, Fruit& fruit, int pop_size, int input_size, int hidden_size, int output_size);

    void mutate();
    Agent crossover();
    void evolve();

};