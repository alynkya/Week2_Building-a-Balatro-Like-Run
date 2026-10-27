#include <cstdlib>
#include <ctime>
#include "GameManager.h"

int main() {
    // Inisialisasi seed random agar fungsi random HandGenerator bekerja dengan baik (Tugas 3)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GameManager gameManager;
    gameManager.runSession();

    return 0;
}