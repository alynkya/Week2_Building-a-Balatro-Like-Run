#pragma once
#include "HandGenerator.h"
#include "ChosenHand.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"

class GameManager {
private:
    HandGenerator handGenerator;
    ChosenHand handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;

public:
    void runSession();
};