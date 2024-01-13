/*!
 * @file Players.hpp
 * @brief Contient les définitions d'un joueur du jeu
 */

#ifndef LEXICON_PLAYER_HPP
#define LEXICON_PLAYER_HPP

#include "Containers/CardList.hpp"


/*!
 * Structure représentant un joueur
 */
struct Player
{
    // La main du joueur
    CardList cards;

    // La somme des scores à la fin de chaque tour + les points de pénalité
    unsigned int score;

    // Si true alors le joueur est éliminé, si false alors le joueur est toujours actif
    bool lost;
};

/*!
 * @brief Ajoute 3 points de pénalité à un joueur (lorsqu'il forme un mot invalide)
 * @param[in, out] player Le joueur qui reçoit des points de pénalité
 */
void ApplyScorePenalty(Player& player);

/*!
 * @brief Met à jour le score d'un joueur à la fin d'un tour, c'est à dire ajoute la somme des points de ses cartes restantes
 * @param[in] player Le joueur dont le score est mis à jour
 * @return true si le joueur a joué le round, false si il avait déjà perdu
 * @note La fonction doit être appelée à la fin d'un tour
 */
void UpdatePlayerScore(Player& player);

/*!
 * @brief Détermine si le joueur actuel a terminé et gagné le tour
 * @param[in] currentPlayer Le joueur passé en paramètre doit être le joueur actuel
 * @return true si le joueur a gagné le tour, false sinon
 * @note La fonction doit être appelée sur le joueur actuel juste après son tour
 */
bool HasPlayerWonRound(const Player& currentPlayer);

#endif //LEXICON_PLAYER_HPP
