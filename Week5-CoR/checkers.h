#ifndef CHECKERS_H
#define CHECKERS_H

#include "models.h"
#include <algorithm>

class PokerHandChecker {
protected:
    PokerHandChecker* nextChecker = nullptr;
public:
    virtual ~PokerHandChecker() = default;
    
    void setNext(PokerHandChecker* next) {
        nextChecker = next;
    }

    virtual HandRank check(const Hand& hand) {
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return HandRank::HIGH_CARD; // Default jika tidak ada yang cocok
    }
};

class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.cards.empty()) return PokerHandChecker::check(hand);
        
        bool isFlush = true;
        Suit firstSuit = hand.cards[0].suit;
        for (size_t i = 1; i < hand.cards.size(); ++i) {
            if (hand.cards[i].suit != firstSuit) {
                isFlush = false;
                break;
            }
        }
        
        if (isFlush) return HandRank::FLUSH;
        return PokerHandChecker::check(hand);
    }
};

class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override {
        if (hand.cards.size() < 5) return PokerHandChecker::check(hand);
        
        // Contoh logika sederhana pengecekan straight berdasarkan urutan rank
        std::vector<int> ranks;
        for (const auto& card : hand.cards) {
            ranks.push_back(static_cast<int>(card.rank));
        }
        std::sort(ranks.begin(), ranks.end());

        bool isStraight = true;
        for (size_t i = 0; i < ranks.size() - 1; ++i) {
            if (ranks[i + 1] != ranks[i] + 1) {
                isStraight = false;
                break;
            }
        }

        if (isStraight) return HandRank::STRAIGHT;
        return PokerHandChecker::check(hand);
    }
};

#endif