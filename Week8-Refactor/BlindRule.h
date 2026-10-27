#pragma once
#include <iostream>

class BlindRule
{
public:
    bool checkBlind(int score)
    {
        int targetBlind = 30;
        bool win = (score >= targetBlind);
        std::cout << "BlindRule checked target (" << targetBlind << "): " << (win ? "WIN" : "LOSE") << "\n";
        return win;
    }
};