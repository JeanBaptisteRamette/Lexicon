#include <cassert>
#include "players.hpp"
#include "definitions.hpp"


void ApplyScorePenalty(Player& player, unsigned int increment)
{
    player.penalty += increment;
}

unsigned int GetTotalScore(const Player& player)
{
    unsigned int scores[CARDS_COUNT_VALUES] = {
            10, 2, 8, 6, 10, 2, 4, 8, 10,
            6, 8, 8, 8, 8, 8, 8, 4, 8,
            8, 8, 8, 8, 8, 2, 4, 2
    };

    unsigned int score = 0;

    for (size_t i = 0; i < ListSize(player.cards); ++i)
    {
        const Card card = CardAt(player.cards, i);
        score += scores[card - 'A'];
    }

    return score + player.penalty;
}


PlayerList PlayerListCreate(size_t playerCount)
{
    assert(playerCount >= MIN_PLAYER_COUNT);
    assert(playerCount <= MAX_PLAYER_COUNT);

    PlayerList players {
        .players = new Player[playerCount],
        .playerCount = playerCount,
        .currentPlayerId = 0
    };

    // Créer une liste de carte vide pour chaque joueur
    for (size_t i = 0; i < playerCount; ++i)
    {
        players.players[i].cards = CardListCreate(CARDS_COUNT_PLAYER);
        players.players[i].penalty = 0;
        players.players[i].lost = false;
    }

    return players;
}

void PlayerListDestroy(PlayerList& players)
{
    // Supprimer les cartes de chaque joueur
    for (size_t i = 0; i < ListSize(players); ++i)
        CardListDestroy(players.players[i].cards);

    // Supprimer les joueurs
    delete[] players.players;
}

size_t ListSize(const PlayerList& players)
{
    return players.playerCount;
}

size_t GetCurrentPlayerId(const PlayerList& players)
{
    return players.currentPlayerId;
}

Player& GetPlayerById(const PlayerList& players, size_t playerId)
{
    assert(playerId < ListSize(players));

    return players.players[playerId];
}

Player& GetCurrentPlayer(const PlayerList& players)
{
    return GetPlayerById(players, GetCurrentPlayerId(players));
}

bool HasPlayerWonRound(const Player& currentPlayer)
{
    return IsEmpty(currentPlayer.cards);
}

void RotateCurrentPlayer(PlayerList& players)
{
    do
    {
        if (players.currentPlayerId == players.playerCount - 1)
            players.currentPlayerId = 0;
        else
            ++players.currentPlayerId;
    } while (GetCurrentPlayer(players).lost);
}



