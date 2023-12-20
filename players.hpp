#ifndef IUT_PROJET2_PLAYERS_HPP
#define IUT_PROJET2_PLAYERS_HPP


#include "definitions.hpp"
#include "cardlist.hpp"


struct Player
{
    CardList cards;
    unsigned int penalty;
};

void ApplyScorePenalty(Player& player, unsigned int increment);
unsigned int GetTotalScore(const Player& player);
bool IsPlayerOut(const Player& player);
bool HasPlayerWonRound(const Player& player);

struct PlayerList
{
    Player* players;
    size_t playerCount;
    size_t currentPlayerId;
};

PlayerList PlayerListCreate(size_t playerCount);
void PlayerListDestroy(PlayerList& players);

size_t ListSize(const PlayerList& players);
size_t GetCurrentPlayerId(const PlayerList& players);

Player& GetPlayerById(const PlayerList& players, size_t playerId);
Player& GetCurrentPlayer(const PlayerList& players);

void RotateCurrentPlayer(PlayerList& players);


#endif //IUT_PROJET2_PLAYERS_HPP
