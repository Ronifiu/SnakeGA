#include "genetic.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(int cols, int rows, int pop_size, int input_size, int hidden_size, int output_size)
    : population_size(pop_size), cols(cols), rows(rows) {
        for (int i = 0; i < pop_size; i++) {
            population.push_back(Agent(cols, rows, Fruit(cols, rows), input_size, hidden_size, output_size));
        }
    }

void GeneticAlgorithm::mutate(Agent& agent, double mutation_rate) {
    for (auto& layer : {&agent.nn.input_to_hidden, &agent.nn.hidden_to_output}) {
        for (auto& row : *layer) {
            for (auto& weight : row) {
                if ((rand() % 1000) / 1000.0 < mutation_rate) {
                    weight += ((rand() % 2000) / 1000.0 - 1.0) * 0.1;
                }
            }
        }
    }
}

vector<double> GeneticAlgorithm::getFitness(vector<Agent>& population) {
    vector<double> fitness_scores;
    for (auto& agent : population) {
        fitness_scores.push_back(agent.fitness);
    }
    return fitness_scores;
}

void crossover_weights(vector<vector<double>>& child_layer, 
    const vector<vector<double>>& parent1_layer, 
    const vector<vector<double>>& parent2_layer) {
    for (size_t i = 0; i < parent1_layer.size(); i++) {
        for (size_t j = 0; j < parent1_layer[0].size(); j++) {
        child_layer[i][j] = (rand() % 2 == 0) ? parent1_layer[i][j] : parent2_layer[i][j];
        }
    }
}

Agent GeneticAlgorithm::crossover(const Agent& parent1, const Agent& parent2) {
    Agent child(cols, rows, Fruit(cols, rows), 
    parent1.nn.input_to_hidden.size(), 
    parent1.nn.hidden_to_output.size(), 
    parent1.nn.hidden_to_output[0].size());

    crossover_weights(child.nn.input_to_hidden, parent1.nn.input_to_hidden, parent2.nn.input_to_hidden);
    crossover_weights(child.nn.hidden_to_output, parent1.nn.hidden_to_output, parent2.nn.hidden_to_output);

    return child;
}


void GeneticAlgorithm::evolve(vector<double> fitness_scores) {
    vector<Agent> new_population;

    vector<int> indices(fitness_scores.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int a, int b) { return fitness_scores[a] > fitness_scores[b]; });

    for (size_t i = 0; i < population_size / 2; i++) {
        new_population.push_back(population[indices[i]]);
        new_population.push_back(crossover(population[indices[i]], population[indices[i + 1]]));
    }

    int elitism_count = max(1.0, population_size * 0.1);

    for (int i = 0; i < elitism_count; i++) {
        new_population.push_back(population[indices[i]]);
    }

    while (new_population.size() < population_size) {
        int parent1_id = indices[rand() % (population_size / 2)];
        int parent2_id = indices[rand() % (population_size / 2)];

        Agent child = crossover(population[parent1_id], population[parent2_id]);

        mutate(child, 0.05);
        
        new_population.push_back(child);
    }
    population = new_population;
}