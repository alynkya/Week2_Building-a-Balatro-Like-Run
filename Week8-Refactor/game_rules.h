#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "models.h"
#include "checkers.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>

class HandGenerator {
public:
    Hand generateHand() {
        // Bentuk deck 52 kartu lalu acak (shuffle) agar setiap generateHand() berbeda
        std::vector<Card> deck;
        for (int s = 0; s < 4; ++s) {
            for (int r = 2; r <= 14; ++r) {
                deck.push_back({static_cast<Rank>(r), static_cast<Suit>(s)});
            }
        }

        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(deck.begin(), deck.end(), rng);

        Hand hand;
        int handSize = 7; // 7 kartu di tangan agar pemain bisa memilih kartu
        for (int i = 0; i < handSize && i < static_cast<int>(deck.size()); ++i) {
            hand.cards.push_back(deck[i]);
        }

        std::cout << "[HandGenerator] Berhasil menghasilkan " << hand.cards.size() << " kartu acak di tangan.\n";
        return hand;
    }
};

// Class ChosenHand sesuai Tugas 1 pada Tugas Design Pattern (1).pdf
class ChosenHand {
private:
    Hand selectedCards;

public:
    void clear() {
        selectedCards.cards.clear();
    }

    void selectFromHand(const Hand& availableHand) {
        clear();
        if (availableHand.cards.empty()) {
            std::cout << "[ChosenHand] Tidak ada kartu tersedia untuk dipilih.\n";
            return;
        }

        std::cout << "\nKartu di tangan Anda:\n";
        for (size_t i = 0; i < availableHand.cards.size(); ++i) {
            std::cout << "  [" << (i + 1) << "] " << availableHand.cards[i].toString() << "\n";
        }

        int count = 0;
        int maxSelect = std::min(5, static_cast<int>(availableHand.cards.size()));
        std::cout << "Berapa kartu yang ingin Anda mainkan (1-" << maxSelect << ")? ";
        std::cin >> count;

        if (std::cin.fail() || count < 1 || count > maxSelect) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "[ChosenHand] Input tidak valid, otomatis memilih 1 kartu pertama.\n";
            selectedCards.cards.push_back(availableHand.cards[0]);
            return;
        }

        for (int i = 0; i < count; ++i) {
            int idx = 0;
            std::cout << "Pilih nomor kartu ke-" << (i + 1) << " (1-" << availableHand.cards.size() << "): ";
            std::cin >> idx;

            if (std::cin.fail() || idx < 1 || idx > static_cast<int>(availableHand.cards.size())) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "  Nomor tidak valid, memilih kartu ke-1 secara default.\n";
                selectedCards.cards.push_back(availableHand.cards[0]);
            } else {
                selectedCards.cards.push_back(availableHand.cards[idx - 1]);
            }
        }
    }

    void playHand() const {
        std::cout << "[ChosenHand] Memainkan kartu pilihan (" << selectedCards.cards.size() << " kartu): ";
        for (const auto& c : selectedCards.cards) {
            std::cout << c.toString() << " ";
        }
        std::cout << "\n";
    }

    const Hand& getSelectedHand() const {
        return selectedCards;
    }
};

class ScoringRule {
public:
    int convertRankToScore(HandRank rank) {
        switch (rank) {
            case HandRank::HIGH_CARD: return 15;
            case HandRank::PAIR:      return 30;
            case HandRank::STRAIGHT:  return 50;
            case HandRank::FLUSH:     return 60;
            default:                  return 15;
        }
    }

    std::string rankToString(HandRank rank) {
        switch (rank) {
            case HandRank::HIGH_CARD: return "HIGH CARD";
            case HandRank::PAIR:      return "PAIR";
            case HandRank::STRAIGHT:  return "STRAIGHT";
            case HandRank::FLUSH:     return "FLUSH";
            default:                  return "HIGH CARD";
        }
    }

    int scoreHand(const Hand& hand) {
        FlushChecker flushCheck;
        StraightChecker straightCheck;
        PairChecker pairCheck;

        flushCheck.setNext(&straightCheck);
        straightCheck.setNext(&pairCheck);

        HandRank detectedRank = flushCheck.check(hand);
        int baseScore = convertRankToScore(detectedRank);

        std::cout << "[ScoringRule] Kombinasi: " << rankToString(detectedRank)
                  << " | Base Score: " << baseScore << "\n";
        return baseScore;
    }
};

class BlindRule {
public:
    bool checkBlind(int score) {
        int targetScore = 40;
        bool success = score >= targetScore;
        std::cout << "[BlindRule] Target Blind: " << targetScore
                  << " | Skor Akhir: " << score
                  << " | Status: " << (success ? "BERHASIL" : "GAGAL") << "\n";
        return success;
    }
};

class RewardRule {
public:
    int earnMoney(bool win, int score) {
        if (!win) {
            std::cout << "[RewardRule] Belum mencapai target blind, uang didapat: $0\n";
            return 0;
        }
        int moneyEarned = 5 + (score / 20);
        std::cout << "[RewardRule] Mendapatkan uang sebesar: $" << moneyEarned << "\n";
        return moneyEarned;
    }
};

#endif