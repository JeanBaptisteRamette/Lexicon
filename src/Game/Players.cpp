/*!
 * @file Players.cpp
 * @brief Implémentation de la gestion des joueurs
 */

#include <cassert>
#include "Players.hpp"
#include "Definitions.hpp"


PlayerList PlayerListCreate(size_t playerCount)
{
    assert(playerCount >= MIN_PLAYER_COUNT);
    assert(playerCount <= MAX_PLAYER_COUNT);

    // Initialiser la liste
    PlayerList players {
        .players = new Player[playerCount],
        .playerCount = playerCount,
        .currentPlayerIndex = 0,
        .roundStarterIndex = 0
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

Player& PlayerAt(const PlayerList& players, size_t index)
{
    assert(index < ListSize(players));

    return players.players[index];
}

Player& GetCurrentPlayer(const PlayerList& players)
{
    return PlayerAt(players, players.currentPlayerIndex);
}


void RotateCurrentPlayer(PlayerList& players)
{
    do
    {
        // Passer au prochain joueur et répéter tant que le nouveau joueur n'est pas actif
        players.currentPlayerIndex = (players.currentPlayerIndex + 1) % players.playerCount;
    }
    while (GetCurrentPlayer(players).lost);
}

void SetRoundStarter(PlayerList& players)
{
    do
    {
        // Passer au prochain joueur et répéter tant que le nouveau joueur n'est pas actif
        players.roundStarterIndex = (players.roundStarterIndex + 1) % players.playerCount;
    }
    while (PlayerAt(players, players.roundStarterIndex).lost);

    // Définir le joueur actuel comme celui qui commence le tour
    players.currentPlayerIndex = players.roundStarterIndex;
}

void UpdateScores(PlayerList& players)
{
    for (size_t i = 0; i < ListSize(players); ++i)
        UpdatePlayerScore(PlayerAt(players, i));
}

void UpdateLosers(PlayerList& players)
{
    unsigned int minimumScore = PlayerAt(players, 0).score;

    // Trouver le score minimum
    for (size_t i = 1; i < ListSize(players); ++i)
        minimumScore = MIN(minimumScore, PlayerAt(players, i).score);

    if (minimumScore >= SCORE_TO_LOSE)
    {
        // Dans le cas où tous les joueurs ont 100 points ou plus,
        // les seuls joueurs gagnants sont ceux qui ont le score le plus bas
		// Si plusieurs joueurs ont le score le plus bas, ils continuent à jouer entre pour déterminer un seul vainqueur
        for (size_t i = 0; i < ListSize(players); ++i)
        {
            Player& player = PlayerAt(players, i);
            player.lost = player.score > minimumScore;
        }
    }
    else
    {
        // Sinon, tous les joueurs avec un score >= 100 perdent
        for (size_t i = 0; i < ListSize(players); ++i)
        {
            Player& player = PlayerAt(players, i);
            player.lost = player.score >= SCORE_TO_LOSE;
        }
    }
}

bool EnoughPlayers(const PlayerList& players)
{
    size_t activePlayerCount = 0;

    // Compter le nombre de joueurs actifs (qui n'ont pas perdu)
    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = PlayerAt(players, i);

        if (!player.lost)
            ++activePlayerCount;
    }

    // La partie peut continuer s'il y a au moins 2 joueur
    return activePlayerCount >= MIN_PLAYER_COUNT;
}
