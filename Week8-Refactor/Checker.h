#pragma once
#include "Hand.h"
#include <iostream>

class Checker
{
public:
    bool checkHand(const Hand &hand)
    {
        // Melengkapi logic untuk class checker (Tugas 2)
        if (hand.cards.empty())
        {
            std::cout << "Checker: Hand is empty!\n";
            return false;
        }
        std::cout << "Checker: Hand validation passed successfully.\n";
        return true;
    }
};