#include "snakeGA.h"

using namespace std;

int main() {
    srand(time(0));
    Fruit fruit(20, 15);
    Agent agent(20, 15, fruit, 14, 28, 4);
    // Snake snake(20, 15, fruit);
    Game game(20, 15, agent, fruit);
    game.run();
    return 0;
}