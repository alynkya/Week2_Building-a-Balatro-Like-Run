#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_rules.h"
#include "ChosenHand.h"
#include <iostream>

class GameManager {
private:
    HandGenerator handGenerator;
    ChosenHand chosenHand; // Integrasi Tugas 1
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    int playerMoney = 0;

public:
    void runSession() {
        std::cout << "=== MEMULAI BALATRO RUN SESSION ===" << std::endl;
        
        for (int round = 1; round <= 3; ++round) {
            std::cout << "\n--- Round " << round << " ---" << std::endl;
            
            // Step 1: Generate Hand
            Hand playerHand = handGenerator.generateHand();
            
            // Step 2: Player plays selected hand (Menggunakan ChosenHand)
            chosenHand.playHand(playerHand);
            
            // Step 3: Score Hand
            int score = scoringRule.scoreHand(playerHand);
            
            // Step 6: Check Blind (Win/Lose)
            bool isWin = blindRule.checkBlind(score);
            
            // Step 7: Earn Money (Reward)
            int moneyGained = rewardRule.earnMoney(isWin, score);
            playerMoney += moneyGained;
            
            std::cout << "Total Uang Saat Ini: $" << playerMoney << std::endl;
        }
        
        std::cout << "\n=== RUN SESSION SELESAI ===" << std::endl;
    }
};

#endif