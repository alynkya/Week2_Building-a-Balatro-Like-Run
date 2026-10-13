#include "game_manager.h"
#include <ctime>
#include <cstdlib>

int main() {
    // Inisialisasi random seed
    srand(static_cast<unsigned int>(time(0)));

    GameManager gameManager;
    gameManager.runSession();

    return 0;
}