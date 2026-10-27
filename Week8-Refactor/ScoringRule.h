#pragma once
#include "Hand.h"
#include <iostream>

class ScoringRule
{
public:
    int scoreHand(const Hand &hand)
    {
        int baseScore = 50; // Contoh kalkulasi skor dasar
        std::cout << "ScoringRule calculated base score: " << baseScore << "\n";
        return baseScore;
    }
};