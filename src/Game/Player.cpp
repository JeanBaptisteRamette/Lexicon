/*!
 * @file Players.cpp
 * @brief Implémentation des fonctions relatives à un joueur
 */

#include "Player.hpp"


void ApplyScorePenalty(Player& player)
{
    player.score += INVALID_WORD_PENALTY;
}

bool HasPlayerWonRound(const Player& currentPlayer)
{
    return IsEmpty(currentPlayer.cards);
}

void UpdatePlayerScore(Player& player)
{
    if (player.lost)
        return;

    // Voir tableau dans l'annexe du sujet
    unsigned int scores[CARDS_COUNT_VALUES] = {
            10, 2, 8, 6, 10, 2, 4, 8, 10,
            6, 8, 8, 8, 8, 8, 8, 4, 8,
            8, 8, 8, 8, 8, 2, 4, 2
    };

    for (size_t i = 0; i < ListSize(player.cards); ++i)
    {
        const Card card = CardAt(player.cards, i);
        player.score += scores[CARD_NO(card)];
    }
}
