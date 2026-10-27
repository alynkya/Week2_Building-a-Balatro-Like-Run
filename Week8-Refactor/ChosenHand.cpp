#include <iostream>
#include "ChosenHand.h"

void ChosenHand::playHand(const Hand& hand) {
    std::cout << "Player plays the chosen hand with " << hand.cards.size() << " cards.\n";
}