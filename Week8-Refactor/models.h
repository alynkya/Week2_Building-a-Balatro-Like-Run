#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <string>
#include <iostream>

enum class Suit
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Rank
{
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

enum class HandRank
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};

struct Card
{
    Rank rank;
    Suit suit;

    std::string toString() const {
        std::string rStr;
        switch (rank) {
            case Rank::JACK:  rStr = "J"; break;
            case Rank::QUEEN: rStr = "Q"; break;
            case Rank::KING:  rStr = "K"; break;
            case Rank::ACE:   rStr = "A"; break;
            default:          rStr = std::to_string(static_cast<int>(rank)); break;
        }

        char sChar;
        switch (suit) {
            case Suit::HEARTS:   sChar = 'H'; break;
            case Suit::DIAMONDS: sChar = 'D'; break;
            case Suit::CLUBS:    sChar = 'C'; break;
            case Suit::SPADES:   sChar = 'S'; break;
        }
        return rStr + sChar;
    }
};

struct Hand
{
    std::vector<Card> cards;
};

// Komponen Joker sesuai alur di Tugas Design Pattern (1).pdf
class JokerCard {
private:
    std::string name;
    int bonusChips;
    int multBonus;

public:
    JokerCard(std::string jokerName = "Greedy Joker", int chips = 15, int mult = 2)
        : name(jokerName), bonusChips(chips), multBonus(mult) {}

    std::string getName() const { return name; }

    void onHandPlayed(int currentScore) const {
        std::cout << "[Joker Observer] " << name << " mendeteksi hand dimainkan (Base Score: "
                  << currentScore << ").\n";
    }

    int modifyScore(int baseScore) const {
        int modified = (baseScore + bonusChips) * multBonus;
        std::cout << "[Joker Effect] " << name << " mengubah skor: ("
                  << baseScore << " + " << bonusChips << ") x " << multBonus
                  << " = " << modified << "\n";
        return modified;
    }
};

#endif