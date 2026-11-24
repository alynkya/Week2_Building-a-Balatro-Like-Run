#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_rules.h"
#include <iostream>

class GameManager {
private:
    HandGenerator handGenerator;
    ChosenHand chosenHand;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    JokerCard jokerCard;
    int playerMoney = 0;

public:
    GameManager() : jokerCard("Jolly Joker", 10, 2) {}

    void runSession() {
        std::cout << "=== Run Started (Joker Aktif: " << jokerCard.getName() << ") ===\n";

        for (int round = 1; round <= 3; ++round) {
            std::cout << "\n--- Round " << round << " ---\n";

            // Step 1: Generate random cards in hand
            Hand playerHand = handGenerator.generateHand();

            // Step 2: Player selects & plays chosen hand
            chosenHand.selectFromHand(playerHand);
            chosenHand.playHand();

            // Step 3: Calculate base score from selected hand
            int score = scoringRule.scoreHand(chosenHand.getSelectedHand());

            // Step 4 & 5: Notify Joker observer & modify score
            jokerCard.onHandPlayed(score);
            score = jokerCard.modifyScore(score);

            // Step 6: Check win / lose against blind
            bool win = blindRule.checkBlind(score);

            // Step 7: Calculate reward & update money
            int reward = rewardRule.earnMoney(win, score);
            playerMoney += reward;
            std::cout << "Money gained: $" << reward << " | Total Money: $" << playerMoney << "\n";
        }

        std::cout << "\n=== Run Ended | Final Money: $" << playerMoney << " ===\n";
    }
};

#endif