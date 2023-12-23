#ifndef IUT_PROJET2_PLAYERS_HPP
#define IUT_PROJET2_PLAYERS_HPP


#include "definitions.hpp"
#include "cardlist.hpp"


struct Player
{
    CardList cards;
    unsigned int penalty;
    bool lost;
};

/*!
 * @brief Ajoute des points de pénalité à un joueur
 * @param[in, out] player Le joueur qui reçoit des points de pénalité
 * @param[in] increment Le nombre de points de pénalité reçus
 */
void ApplyScorePenalty(Player& player, unsigned int increment);

/*!
 * @brief Calcul le score d'un joueur, c'est à dire la somme des points de ses cartes restantes
 *        plus les points de pénalités
 * @param[in] player Le joueur dont le score est calculé
 * @return Le score du joueur
 */
unsigned int GetTotalScore(const Player& player);

/*!
 * @brief Détermine si le joueur actuel a terminé et gagné le tour
 * @param[in] currentPlayer Le joueur passé en paramètre doit être le joueur actuel
 * @return true si le joueur a gagné le tour, false sinon
 */
bool HasPlayerWonRound(const Player& currentPlayer);


struct PlayerList
{
    Player* players;
    size_t playerCount;
    size_t currentPlayerId;
};

/*!
 * @brief Créer la liste des joueurs de Lexicon
 * @param[in] playerCount Le nombre de joueur
 * @return La liste des joueurs, aucun n'a de carte ou de points de pénalité
 * @pre playerCount >= MIN_PLAYER_COUNT
 * @pre playerCount <= MAX_PLAYER_COUNT
 */
PlayerList PlayerListCreate(size_t playerCount);

/*!
 * @brief Désalloue la liste de joueurs, ainsi que leur cartes qui sont aussi allouées dynamiquement
 * @param[in, out] players La liste des joueurs à désallouer
 */
void PlayerListDestroy(PlayerList& players);

/*!
 * @brief Retourne le nombre de joueur dans la liste (qu'ils soient éliminés ou pas)
 * @param players La liste des joueurs
 * @return Le nombre de joueurs dans la liste
 */
size_t ListSize(const PlayerList& players);

/*!
 * @brief Retourne l'indice du joueur actuel dans la liste
 * @param[in] players La liste des joueurs
 * @return L'indice i du joueur actuel 0 <= i < ListSize(players)
 */
size_t GetCurrentPlayerId(const PlayerList& players);

/*!
 * @brief Retourne le joueur à l'indice playerId de la liste
 * @param[in] players La liste des joueurs
 * @param[in] playerId L'indice du joueur dans la liste
 * @return Référence vers le joueur associé à l'indice
 * @pre playerId < ListSize(players)
 */
Player& GetPlayerById(const PlayerList& players, size_t playerId);

/*!
 * @brief Récupère le joueur actuel
 * @param[in] players La liste des joueurs
 * @return Référence vers le joueur actuel
 */
Player& GetCurrentPlayer(const PlayerList& players);

/*!
 * @brief Mets à jour le joueur actuel après que le précédent ait finit de joueur
 * @param players[in, out] La liste des joueurs
 */
void RotateCurrentPlayer(PlayerList& players);


#endif //IUT_PROJET2_PLAYERS_HPP
