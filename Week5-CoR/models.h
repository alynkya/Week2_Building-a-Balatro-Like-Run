#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <string>

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
};

struct Hand
{
    std::vector<Card> cards;
};

#endif