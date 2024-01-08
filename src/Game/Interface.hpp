#ifndef LEXICON_INTERFACE_HPP
#define LEXICON_INTERFACE_HPP


#include <sstream>
#include "Definitions.hpp"
#include "Players.hpp"
#include "Containers/WordList.hpp"
#include "Containers/CardList.hpp"
#include "Containers/CardStack.hpp"
#include "GameData.hpp"

struct Command
{
    char name;
    size_t wordIndex;
    Card card;
    CardList cards;
};

/*!
 * @brief Lis le nombre de joueurs, passé en ligne de commande
 * @param[in] argc Le nombre d'argument du programme
 * @param[in] argv Les arguments du programme
 * @return Le nombre de joueurs voulue par l'utilisateur, 0 si invalide
 */
unsigned int ReadPlayerCount(int argc, const char* argv[]);

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
 * @param[in] game Les données du jeu
 */
void DisplayGameState(const GameData& game);

/*!
 * @brief Affiche les scores de chaque joueurs encore actif à la fin d'un tour.
 * @param[in] players La liste des joueurs
 */
void DisplayScores(const PlayerList& players);

/*!
 * @brief Affiche un message lorsque la partie est finie
 */
void DisplayGameOver();

/*!
 * @brief Lis une commande et ses paramètres, saisis par le joueur actuel
 * @param[in, out] cmd La structure contenant le nom de la commande et ses paramètres
 * @return true si la commande est correctement formée, false si elle doit être re-saisis
 */
bool ReadPlayerCommand(Command& cmd);

/*!
 * @brief Lit une commande utilisateur depuis un stream
 * @param[out] cmd Contient les données de la commande saisie
 * @param[in, out] stream Le flot qui contient la ligne de commande saisie par le joueur
 * @return true si la commande est correctement formée, false si non
 * @note On sépare cette fonction pour pouvoir la tester dans les tests unitaires
 */
bool ReadCommandFromStream(Command& cmd, std::istringstream& stream);


#endif //LEXICON_INTERFACE_HPP
