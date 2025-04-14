
#include "simulation.h"

using namespace std;

Simulation::Simulation(int cols, int rows, int population_size, int input_size, int hidden_size, int output_size) 
    : cols(cols), rows(rows), population_size(population_size), input_size(input_size), hidden_size(hidden_size), output_size(output_size) {}

void Simulation::run(int maxgen) {
    GeneticAlgorithm ga(cols, rows, population_size, input_size, hidden_size, output_size);

    for (int i = 0; i < maxgen; i++) {
        
        // Run all agents in headless mode
        for (auto& agent : ga.population) {
            Game simulationGame(cols, rows, agent, agent.fruit, false);
            simulationGame.run();
        }

        int best_index = max_element(ga.population.begin(), ga.population.end(), 
        [](const Agent& a, const Agent& b) { return a.fitness < b.fitness; }) - ga.population.begin();
        cout << ga.population[best_index].fitness << endl;
        // Display best agent
        if (i%10 == 0) {
            Game displayGen(cols, rows, ga.population[best_index], ga.population[best_index].fruit, true);
            displayGen.run();
        }

        // Evolve population
        ga.evolve(ga.getFitness(ga.population));
    }
}