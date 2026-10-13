#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "models.h"
#include "checkers.h"
#include <cstdlib>
#include <iostream>

class HandGenerator
{
public:
    Hand generateHand()
    {
        Hand hand;
        // Simulasi menghasilkan 5 kartu random untuk pemain
        for (int i = 0; i < 5; ++i)
        {
            Card c;
            c.rank = static_cast<Rank>((rand() % 13) + 2);
            c.suit = static_cast<Suit>(rand() % 4);
            hand.cards.push_back(c);
        }
        std::cout << "[HandGenerator] Berhasil menghasilkan kartu tangan baru." << std::endl;
        return hand;
    }
};

class ScoringRule
{
public:
    int convertRankToScore(HandRank rank)
    {
        switch (rank)
        {
        case HandRank::HIGH_CARD:
            return 10;
        case HandRank::PAIR:
            return 20;
        case HandRank::STRAIGHT:
            return 40;
        case HandRank::FLUSH:
            return 50;
        default:
            return 10;
        }
    }

    int scoreHand(const Hand &hand)
    {
        FlushChecker flushCheck;
        StraightChecker straightCheck;

        flushCheck.setNext(&straightCheck);

        HandRank detectedRank = flushCheck.check(hand);
        int baseScore = convertRankToScore(detectedRank);

        std::cout << "[ScoringRule] Kombinasi kartu terdeteksi, Base Score: " << baseScore << std::endl;
        return baseScore;
    }
};

class BlindRule
{
public:
    bool checkBlind(int score)
    {
        int targetScore = 30; // Target minimum skor untuk mengalahkan blind
        bool success = score >= targetScore;
        std::cout << "[BlindRule] Target Blind: " << targetScore << " | Skor Pemain: " << score
                  << " | Status Win: " << (success ? "BERHASIL" : "GAGAL") << std::endl;
        return success;
    }
};

class RewardRule
{
public:
    int earnMoney(bool win, int score)
    {
        if (!win)
            return 0;
        int moneyEarned = 5 + (score / 10);
        std::cout << "[RewardRule] Pemain mendapatkan uang sebesar: $" << moneyEarned << std::endl;
        return moneyEarned;
    }
};

#endif