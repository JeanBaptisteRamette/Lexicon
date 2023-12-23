#ifndef IUT_PROJET2_GAMEINTERFACE_HPP
#define IUT_PROJET2_GAMEINTERFACE_HPP


#include "definitions.hpp"
#include "players.hpp"
#include "wordlist.hpp"
#include "cardlist.hpp"
#include "cardstack.hpp"


struct Command
{
    char name;
    size_t wordIndex;
    Card card;
    CardList cards;
};

/*!
 * @brief Affiche les commandes valides du jeu
 */
void DisplayValidCommands();

/*!
 * @brief Affiche un message d'erreur lorsque la commande est invalide
 */
void DisplayInvalidCommand();

/*!
 * @brief Affiche un message d'erreur lorsque le mot est invalide
 */
void DisplayInvalidWord();

/*!
 * @brief Affiche l'état du jeu, c'est à dire: le joueur actuel, la première carte exposée
 *        et les mots placés sur la table
 * @param[in] players La liste des joueurs
 * @param[in] exposedCards La pile des cartes exposées
 * @param[in] placedWords La liste des mots placés sur la table
 */
void DisplayGameState(const PlayerList& players, const CardStack& exposedCards, const WordList& placedWords);

/*!
 * @brief Affiche les scores de chaque joueurs à la fin d'un tour
 * @param[in] players La liste des joueurs
 */
void DisplayScores(const PlayerList& players);

/*!
 * @brief Affiche un message lorsque la partie est finie
 */
void DisplayGameOver();

bool ReadPlayerCommand(Command& cmd);


#endif //IUT_PROJET2_GAMEINTERFACE_HPP
