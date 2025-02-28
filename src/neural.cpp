#include "neural.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size) {
    input_to_hidden = randomMatrix(input_size, hidden_size);
    hidden_to_output = randomMatrix(hidden_size, output_size);
    hidden_bias = randomVector(hidden_size);
    output_bias = randomVector(output_size);
}

vector<double> NeuralNetwork::forward(vector<double> inputs) {
    vector<double> hidden = activate(matrixMultiply(inputs, input_to_hidden, hidden_bias));
    return softmax(matrixMultiply(hidden, hidden_to_output, output_bias));
}

vector<vector<double>> NeuralNetwork::randomMatrix(int rows, int cols) {
    vector<vector<double>> matrix(rows, vector<double>(cols)); // init matrix
    // loop through every value:
    for (auto& row : matrix) {
        for (auto& val : row) {
            val = ((rand() % 2000) / 1000.0) - 1.0; // random values in [-1,1]
        }
    }
    return matrix;
}

vector<double> NeuralNetwork::randomVector(int size) {
    vector<double> vector(size);
    for (auto& val : vector) {
        val = ((rand() % 2000) / 1000.0) - 1.0;
    }
    return vector;
}

vector<double> NeuralNetwork::matrixMultiply(const vector<double>& input, const vector<vector<double>>& weights, const vector<double>& bias) {
    vector<double> output(weights[0].size(), 0.0);
    for (size_t j = 0; j < weights[0].size(); j++) {
        for (size_t i = 0; i < input.size(); i++) {
            output[j] = input[i] * weights[i][j];
        }
        output[j] += bias[j];
    }
    return output;
}

vector<double> NeuralNetwork::activate(vector<double> values) {
    for (double& val : values) {
        val = max(0.0, val);
    }
    return values;
}

vector<double> NeuralNetwork::softmax(vector<double> values) {
    double sum = 0.0;
    for (double val : values) sum += exp(val);
    for (double& val : values) val = exp(val) / sum;
    return values;
}
