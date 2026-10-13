#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <memory>
#include <string>

// Struktur Data State Game
struct GameState
{
    int playerHp = 100;
    int enemyHp = 50;
    int currentTurn = 1;
    bool isGameOver = false;
};

// Interface untuk Aksi Pemain (Mutable Mechanics)
class IPlayerAction
{
public:
    virtual ~IPlayerAction() = default;
    virtual int executeAction() = 0; // Mengembalikan besar damage/aksi
};

// Interface untuk Resolusi Sistem / Combat (Mutable Mechanics)
class ICombatResolver
{
public:
    virtual ~ICombatResolver() = default;
    virtual void resolve(int playerActionValue, GameState &state) = 0;
};

// Interface untuk Pemberian Reward (Mutable Mechanics)
class IRewardSystem
{
public:
    virtual ~IRewardSystem() = default;
    virtual void giveReward(GameState &state) = 0;
};

// Kelas Utama Pengontrol Loop (Invariant Structure)
class GameSession
{
private:
    GameState state;
    std::unique_ptr<IPlayerAction> playerAction;
    std::unique_ptr<ICombatResolver> combatResolver;
    std::unique_ptr<IRewardSystem> rewardSystem;

public:
    GameSession(std::unique_ptr<IPlayerAction> action,
                std::unique_ptr<ICombatResolver> resolver,
                std::unique_ptr<IRewardSystem> reward)
        : playerAction(std::move(action)),
          combatResolver(std::move(resolver)),
          rewardSystem(std::move(reward)) {}

    void startGame()
    {
        std::cout << "=== GAME SESSION STARTED ===" << std::endl;

        // Invariant Loop: Urutan ini tidak boleh diubah
        while (!state.isGameOver)
        {
            std::cout << "\n--- Turn " << state.currentTurn << " ---" << std::endl;

            // 1. Player does action
            int actionValue = playerAction->executeAction();

            // 2. System evaluates / resolves combat
            combatResolver->resolve(actionValue, state);

            // 3. Reward or penalty is given
            if (state.enemyHp <= 0 && !state.isGameOver)
            {
                rewardSystem->giveReward(state);
            }

            // 4. Game state updates & Check win/lose condition
            if (state.playerHp <= 0)
            {
                std::cout << "[STATE] Player kalah! Game Over." << std::endl;
                state.isGameOver = true;
            }
            else if (state.enemyHp <= 0)
            {
                std::cout << "[STATE] Musuh dikalahkan! Anda Menang!" << std::endl;
                state.isGameOver = true;
            }
            else
            {
                state.currentTurn++;
            }
        }

        std::cout << "=== GAME SESSION ENDED ===" << std::endl;
    }
};

#endif