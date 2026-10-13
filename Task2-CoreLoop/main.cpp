#include "core.h"
#include "game.h"
#include <ctime>

int main() {
    // Inisialisasi random seed
    srand(static_cast<unsigned int>(time(0)));

    // Membuat instance komponen (Mutable elements)
    auto playerAction = std::make_unique<StandardPlayerAction>();
    auto combatResolver = std::make_unique<StandardCombatResolver>();
    auto rewardSystem = std::make_unique<StandardRewardSystem>();

    // Memasukkan komponen ke dalam GameSession (Invariant Loop)
    GameSession session(
        std::move(playerAction),
        std::move(combatResolver),
        std::move(rewardSystem)
    );

    // Menjalankan game loop
    session.startGame();

    return 0;
}