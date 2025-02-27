#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

class NeuralNetwork {
public:
    std::vector<std::vector<double>> input_to_hidden;
    std::vector<std::vector<double>> hidden_to_output;
    std::vector<double> hidden_bias;
    std::vector<double> output_bias;

    NeuralNetwork(int input_size, int hidden_size, int output_size);
    
    std::vector<double> forward(std::vector<double> inputs);
private:
    std::vector<std::vector<double>> randomMatrix(int rows, int cols);
    std::vector<double> randomVector(int size);
    std::vector<double> matrixMultiply(const std::vector<double>& input, const std::vector<std::vector<double>>& weights, const std::vector<double>& bias);
    std::vector<double> activate(std::vector<double> values);
    std::vector<double> softmax(std::vector<double> values);
};
