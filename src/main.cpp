#include "snakeGA.h"

using namespace std;

int main() {
    srand(time(0));
    Simulation simulation(30, 30, 100, 24, 48, 4);
    simulation.run(100);
    return 0;
}