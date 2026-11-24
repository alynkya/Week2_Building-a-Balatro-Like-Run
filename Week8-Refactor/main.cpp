#include "game_manager.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    GameManager gameManager;
    gameManager.runSession();

    return 0;
}