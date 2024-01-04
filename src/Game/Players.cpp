/*!
 * @file Players.cpp
 * @brief Implémentation de la gestion des joueurs
 */

#include <cassert>
#include "Players.hpp"
#include "Definitions.hpp"


void ApplyScorePenalty(Player& player)
{
    player.score += INVALID_WORD_PENALTY;
}

unsigned int GetPlayerScore(const Player& player)
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
        score += scores[CARD_NO(card)];
    }

    return score;
}


PlayerList PlayerListCreate(size_t playerCount)
{
    assert(playerCount >= MIN_PLAYER_COUNT);
    assert(playerCount <= MAX_PLAYER_COUNT);

    PlayerList players {
        .players = new Player[playerCount],
        .playerCount = playerCount,
        .currentPlayerIndex = 0
    };

    // Créer une liste de carte vide pour chaque joueur
    for (size_t i = 0; i < playerCount; ++i)
    {
        players.players[i].cards = CardListCreate(CARDS_COUNT_PLAYER);
        players.players[i].score = 0;
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
    return players.currentPlayerIndex + 1;
}

size_t GetCurrentPlayerIndex(const PlayerList& players)
{
    return players.currentPlayerIndex;
}

Player& PlayerAt(const PlayerList& players, size_t index)
{
    assert(index < ListSize(players));

    return players.players[index];
}

Player& GetCurrentPlayer(const PlayerList& players)
{
    return PlayerAt(players, players.currentPlayerIndex);
}

bool HasPlayerWonRound(const Player& currentPlayer)
{
    return IsEmpty(currentPlayer.cards);
}

void RotateCurrentPlayer(PlayerList& players)
{
    //
    // Trouve le prochain joueur encore actif
    //
    do
    {
        if (players.currentPlayerIndex == players.playerCount - 1)
            players.currentPlayerIndex = 0;
        else
            ++players.currentPlayerIndex;
    }
    while (GetCurrentPlayer(players).lost);
}

void SetRoundStarter(PlayerList& players, size_t& starterIndex)
{
    assert(starterIndex < ListSize(players));

    // Revenir au joueur qui a commencé le tour précédent
    players.currentPlayerIndex = starterIndex;

    // Trouver le prochain joueur actif
    RotateCurrentPlayer(players);

    // Actualiser l'indice du joueur qui a commencé le tour
    starterIndex = GetCurrentPlayerIndex(players);
}

void UpdateScores(PlayerList& players)
{
    for (size_t i = 0; i < ListSize(players); ++i)
    {
        Player& player = PlayerAt(players, i);

        player.score += GetPlayerScore(player);

        //
        // Vérifier si le joueur dépasse le score maximal, et le rendre inactif si c'est le cas
        //
        if (player.score >= SCORE_TO_LOSE)
            player.lost = true;
    }
}

bool EnoughPlayers(const PlayerList& players)
{
    size_t activePlayerCount = 0;

    //
    // Compter le nombre de joueurs actifs (qui n'ont pas perdu)
    //
    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = PlayerAt(players, i);

        if (!player.lost)
            ++activePlayerCount;
    }

    //
    // La partie peut continuer s'il le joueur n'est pas seul
    //
    return activePlayerCount >= MIN_PLAYER_COUNT;
}
