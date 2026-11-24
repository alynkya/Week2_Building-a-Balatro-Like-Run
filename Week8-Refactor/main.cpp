#include "game_manager.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <limits>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    GameManager gameManager;
    gameManager.runSession();

    std::cout << "\nTekan Enter untuk keluar dari program...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}