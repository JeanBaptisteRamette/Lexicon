#ifndef IUT_PROJET2_GAMELOGIC_HPP
#define IUT_PROJET2_GAMELOGIC_HPP

#include "gameinterface.hpp"
#include "cardlist.hpp"
#include "wordlist.hpp"
#include "cardstack.hpp"
#include "players.hpp"


/*!
 * @brief Créer le paquet de carte avant distribution selon les règles
 * @return Le paquet de carte
 */
CardList CreateGameCards();

/*!
 * @brief Mélange une liste de cartes
 * @param[in, out] cards Les cartes à mélanger
 */
void ShuffleCards(CardList& cards);

/*!
 * @brief Distribue une liste de cartes à une liste de joueurs
 * @param[in, out] players Les joueurs à qui distribuer
 * @param[in] cards Les cartes à distribuer
 */
void DistributeCards(PlayerList& players, CardList& cards);

/*!
 * @brief Détermine si la partie est terminée, c'est à dire qu'il n'y a plus qu'un joueur restant
 * @param[in] players La liste des joueurs
 * @return true si la partie est terminée, false sinon
 */
bool IsGameOver(const PlayerList& players);

/*!
 * @brief Elimine les joueurs qui dépassent 100 points après la fin d'un tour
 * @param[in, out] players
 */
void UpdateLosers(PlayerList& players);

/*!
 * @brief Lit le dictionnaire de mot valides depuis le fichier "ods4.txt"
 * @return La liste de mot
 */
WordList ReadDictionary();

/*!
 * @brief Implémente la commande 'T' du jeu
 * @param[in, out] player Le joueur actuel
 * @param[in, out] exposedCards La pile des cartes exposées
 * @param[in, out] talonCards La pile des cartes invisibles
 */
void CommandTalon(const Command& cmd, Player& player, CardStack& exposedCards, CardStack& talonCards);

/*!
 * @brief Implémente la commande 'E' du jeu
 * @param[in, out] player Le joueur actuel
 * @param[in, out] exposedCards La pile des cartes exposées
 */
void CommandExposed(const Command& cmd, Player& player, CardStack& exposedCards);

/*!
 * @brief Implémente la commande 'P' du jeu
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
void CommandPlace(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary);

/*!
 * @brief Implémente la commande 'R' du jeu
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
void CommandReplace(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary);

/*!
 * @brief Implémente la commande 'C' du jeu
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
void CommandComplete(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary);

#endif //IUT_PROJET2_GAMELOGIC_HPP
