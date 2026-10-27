#pragma once
#include <iostream>

class RewardRule
{
public:
    int earnMoney(bool win, int score)
    {
        if (!win)
            return 0;
        int reward = 10 + (score / 5);
        return reward;
    }
};