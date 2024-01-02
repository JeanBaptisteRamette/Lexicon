/*!
 * @file Players.hpp
 * @brief Contient les définitions des fonctions reliées aux joueurs
 */

#ifndef LEXICON_PLAYERS_HPP
#define LEXICON_PLAYERS_HPP


#include "Containers/CardList.hpp"


/*!
 * Structure représentant un joueur
 */
struct Player
{
    // La main du joueur
    CardList cards;

    // La somme des scores à la fin de chaque round + les points de pénalité
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
 * @brief Calcul le score d'un joueur à la fin d'un tour, c'est à dire la somme des points de ses cartes restantes
 * @param[in] player Le joueur dont le score est calculé
 * @return Le score du joueur
 * @note La fonction doit être appelée à la fin d'un tour
 */
unsigned int GetPlayerScore(const Player& player);

/*!
 * @brief Détermine si le joueur actuel a terminé et gagné le tour
 * @param[in] currentPlayer Le joueur passé en paramètre doit être le joueur actuel
 * @return true si le joueur a gagné le tour, false sinon
 * @note La fonction doit être appelée sur le joueur actuel juste après son tour
 */
bool HasPlayerWonRound(const Player& currentPlayer);


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
 * @brief Mets à jour le joueur actuel après que le précédent ait finit de joueur
 * @param[in, out] players La liste des joueurs
 * @note Il faut être sûr qu'au moins un joueur est toujours actif, pour éviter une boucle infinie
 */
void RotateCurrentPlayer(PlayerList& players);

/*!
 * @brief Met à jour le score et élimine les joueurs qui dépassent 100 points après la fin d'un tour
 * @param[in, out] players Liste des joueurs
 */
void UpdateScores(PlayerList& players);

#endif //LEXICON_PLAYERS_HPP
