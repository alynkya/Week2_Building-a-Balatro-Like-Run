#include <iostream>
#include <cstdlib>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating random hand...\n";
    Hand hand;
    
    // Memperbaiki logic agar kartu yang muncul di hand menjadi random (Tugas 3)
    for (int i = 0; i < 5; ++i) {
        int randomRank = (rand() % 13) + 2; // Menghasilkan rank 2 s.d. 14 (Ace)
        char suits[] = {'H', 'D', 'C', 'S'};
        char randomSuit = suits[rand() % 4]; // Menghasilkan suit acak ('H', 'D', 'C', 'S')
        
        hand.cards.push_back({randomRank, randomSuit});
    }

    // Menampilkan kartu yang berhasil digenerate
    for (const auto& card : hand.cards) {
        std::cout << "[Card Generated] Rank: " << card.rank << ", Suit: " << card.suit << "\n";
    }

    return hand;
}