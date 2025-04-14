#pragma once

#include <vector>
#include <numeric>
#include <algorithm>

#include "agent.h"
#include "fruit.h"

class GeneticAlgorithm {
public:
    std::vector<Agent> population;
    int population_size;
    int cols, rows;

    GeneticAlgorithm(int cols, int rows, int pop_size, int input_size, int hidden_size, int output_size);

    void mutate(Agent& agent, double mutation_rate);
    Agent crossover(const Agent& parent1, const Agent& parent2);
    void evolve(std::vector<double> fitness_scores);
    std::vector<double> getFitness(std::vector<Agent>& population);

};