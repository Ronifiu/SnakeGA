#include "genetic.h"

GeneticAlgorithm::GeneticAlgorithm(int cols, int rows, Fruit& fruit, int pop_size, int input_size, int hidden_size, int output_size)
    : population_size(pop_size), cols(cols), rows(rows), fruit(fruit) {
        for (int i = 0; i < pop_size; i++) {
            population.push_back(Agent(cols, rows, fruit, input_size, hidden_size, output_size));
        }
    }

//void GeneticAlgorithm::mutate(NeuralNetwork& nn) {}