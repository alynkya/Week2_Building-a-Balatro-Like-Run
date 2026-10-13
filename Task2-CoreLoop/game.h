#ifndef GAME_H
#define GAME_H

#include "core.h"
#include <cstdlib>

// Implementasi Aksi Pemain (Mutable)
class StandardPlayerAction : public IPlayerAction {
public:
    int executeAction() override {
        int damage = (rand() % 15) + 10; // Serangan acak 10-24
        std::cout << "1. Player menyerang musuh sebesar " << damage << " damage." << std::endl;
        return damage;
    }
};

// Implementasi Resolusi Combat (Mutable)
class StandardCombatResolver : public ICombatResolver {
public:
    void resolve(int playerActionValue, GameState& state) override {
        // Kurangi HP musuh
        state.enemyHp -= playerActionValue;
        if (state.enemyHp < 0) state.enemyHp = 0;
        std::cout << "2. Sistem memproses: HP Musuh tersisa " << state.enemyHp << std::endl;

        // Jika musuh masih hidup, musuh membalas menyerang player
        if (state.enemyHp > 0) {
            int counterDamage = (rand() % 10) + 5;
            state.playerHp -= counterDamage;
            if (state.playerHp < 0) state.playerHp = 0;
            std::cout << "   Musuh membalas! Player menerima " << counterDamage << " damage. HP Player: " << state.playerHp << std::endl;
        }
    }
};

// Implementasi Sistem Reward (Mutable)
class StandardRewardSystem : public IRewardSystem {
public:
    void giveReward(GameState& state) override {
        std::cout << "3. Reward diberikan: +50 Gold dan pemulihan HP kecil!" << std::endl;
        state.playerHp += 20; // Bonus pemulihan
    }
};

#endif