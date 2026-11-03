#ifndef CHOSEN_HAND_H
#define CHOSEN_HAND_H

#include "models.h"
#include <iostream>

class ChosenHand {
public:
    void playHand(const Hand& hand) {
        std::cout << "[ChosenHand] Pemain memilih dan memainkan kartu tangan (" << hand.cards.size() << " kartu):\n";
        for (const auto& card : hand.cards) {
            std::cout << "  -> Rank: " << static_cast<int>(card.rank) 
                      << ", Suit: " << static_cast<int>(card.suit) << "\n";
        }
    }
};

#endif