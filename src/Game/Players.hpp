/*!
 * @file Players.hpp
 * @brief Contient les définitions des fonctions reliées à la liste des joueurs du jeu
 */

#ifndef LEXICON_PLAYERS_HPP
#define LEXICON_PLAYERS_HPP


#include "Player.hpp"


/*!
 * Structure représentant la liste des joueurs du jeu, actifs ou éliminés
 */
struct PlayerList
{
    // Pointeurs vers les joueurs du jeu
    Player* players;

    // Le nombre de joueurs dans la liste, MIN_PLAYER_COUNT <= playerCount <= MAX_PLAYER_COUNT
    size_t playerCount;

    // L'indice dans la liste du joueur actuel, 0 <= currentPlayerIndex < playerCount
    size_t currentPlayerIndex;

    // L'indice du joueur qui a commencé le tour
    size_t roundStarterIndex;
};

/*!
 * @brief Créer la liste des joueurs de Lexicon
 * @param[in] playerCount Le nombre de joueur
 * @return La liste des joueurs, aucun n'a de carte ou de points de pénalité
 * @pre MIN_PLAYER_COUNT <= playerCount <= MAX_PLAYER_COUNT
 */
PlayerList PlayerListCreate(size_t playerCount);

/*!
 * @brief Désalloue la liste de joueurs alloués par PlayerListCreate
 * @param[in, out] players La liste des joueurs à désallouer
 * @note La fonction désalloue aussi les listes de carte des joueurs
 */
void PlayerListDestroy(PlayerList& players);

/*!
 * @brief Retourne le nombre de joueur dans la liste (qu'ils soient éliminés ou pas)
 * @param[in] players La liste des joueurs
 * @return Le nombre de joueurs dans la liste
 */
size_t ListSize(const PlayerList& players);

/*!
 * @brief Retourne l'identifiant (et pas l'indice) du joueur actuel
 * @param[in] players La liste des joueurs
 * @return L'identifiant du joueur actuel tel que 1 <= id <= ListSize(players)
 */
size_t GetCurrentPlayerId(const PlayerList& players);

/*!
 * @brief Retourne le joueur à l'indice index de la liste
 * @param[in] players La liste des joueurs
 * @param[in] index L'indice du joueur dans la liste
 * @return Référence vers le joueur associé à l'indice
 * @pre index < ListSize(players)
 */
Player& PlayerAt(const PlayerList& players, size_t index);

/*!
 * @brief Récupère le joueur actuel
 * @param[in] players La liste des joueurs
 * @return Référence vers le joueur actuel
 */
Player& GetCurrentPlayer(const PlayerList& players);

/*!
 * @brief Met à jour le joueur actuel après que le précédent ait finit de joueur
 * @param[in, out] players La liste des joueurs
 * @note Il faut être sûr qu'au moins un joueur est toujours actif, pour éviter une boucle infinie
 */
void RotateCurrentPlayer(PlayerList& players);

/*!
 * @brief Met à jour le joueur qui commence le tour,
 *        c'est à dire le prochain joueur actif après celui qui a commencé le tour précédent
 * @param[in, out] players La liste des joueurs
 */
void SetRoundStarter(PlayerList& players);

/*!
 * @brief Met à jour le score et des joueurs après la fin d'un tour
 * @param[in, out] players Liste des joueurs
 */
void UpdateScores(PlayerList& players);

void UpdateLosers(PlayerList& players);

/*!
 * @brief Détermine si il y a assez de joueur actif pour joueur, autrement dit, si la partie est fini ou non
 * @param[in] players La liste des joueurs
 * @return true si il y a assez de joueur pour continuer à jouer, false sinon
 */
bool EnoughPlayers(const PlayerList& players);

#endif //LEXICON_PLAYERS_HPP
