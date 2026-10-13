#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_rules.h"
#include <iostream>

class GameManager {
private:
    HandGenerator handGenerator;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    int playerMoney = 0;

public:
    void runSession() {
        std::cout << "=== MEMULAI BALATRO RUN SESSION ===" << std::endl;
        
        // Simulasi 3 putaran permainan (Round / Blind)
        for (int round = 1; round <= 3; ++round) {
            std::cout << "\n--- Round " << round << " ---" << std::endl;
            
            // 1. Generate Hand
            Hand playerHand = handGenerator.generateHand();
            
            // 2. Score Hand
            int score = scoringRule.scoreHand(playerHand);
            
            // 3. Check Blind
            bool isWin = blindRule.checkBlind(score);
            
            // 4. Earn Money
            int moneyGained = rewardRule.earnMoney(isWin, score);
            playerMoney += moneyGained;
            
            std::cout << "Total Uang Saat Ini: $" << playerMoney << std::endl;
        }
        
        std::cout << "\n=== RUN SESSION SELESAI ===" << std::endl;
    }
};

#endif