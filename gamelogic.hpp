#ifndef IUT_PROJET2_GAMELOGIC_HPP
#define IUT_PROJET2_GAMELOGIC_HPP

#include "gameinterface.hpp"
#include "cardlist.hpp"
#include "wordlist.hpp"
#include "cardstack.hpp"
#include "players.hpp"
#include "gamedata.hpp"


/*!
 * @brief Recycle la pile des cartes exposées pour remplir le talon lorsqu'il est vide
 * @param[in, out] talonCards La pile représentant les cartes du talon
 * @param[in, out] exposedCards La pile représentant les cartes exposées
 * @pre La pile des cartes exposées ne doit pas être vide
 */
void ReuseExposedCards(CardStack& talonCards, CardStack& exposedCards);


/*!
 * @brief Joue au jeu après l'initialisation des données nécessaires au jeu
 * @param[in, out] game Les données nécéssaires au jeu, initialisé avec InitGameData
 */
void GameRun(GameData& game);


/*!
 * @brief Exécute une commande utilisateur
 * @param[in] cmd
 * @param[in, out] game
 * @return true si la commande est valide et que le joueur a donc finit son tour,
 *         false si la commande est invalide et que le joueur doit rejouer son tour
 */
bool ExecuteCommand(const CommandParams& cmd, GameData& game);

/*!
 * @brief Créer le paquet de carte contenant toutes les cartes du jeu
 *        selon les règles
 * @return Le paquet de carte, non mélangé
 */
CardStack CreateGameCards();

/*!
 * @brief Mélange une liste de cartes quelconque
 * @param[in, out] cards Les cartes à mélanger
 */
void ShuffleCards(CardList& cards);

/*!
 * @brief Distribue une liste de cartes à une liste de joueurs
 * @param[in, out] players Les joueurs à qui distribuer
 * @param[in, out] cards Les cartes à distribuer
 * @note Distribue au maximum ListSize(players) * 10 cartes
 */
void DistributeCards(PlayerList& players, CardStack& cards);

/*!
 * @brief Reprend toutes les cartes du jeu
 * @param game
 */
void RedistributeCards(GameData& game);

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
 * @brief Vérifie si le joueur à les cartes cards, autrement dit si il peut former le mot cards avec sa main
 * @param[in] player Le joueur pour qui vérifier la main
 * @param[in] cards Le mot à former
 * @return true si le jouer peut former le mot false sinon
 */
bool HasCards(const Player& player, const CardList& cards);

/*!
 * @brief Vérifie si un mot est valide selon un dictionnaire
 * @param[in] dictionary Dictionnaire de mot vaide
 * @param[in] word Le mot à vérifier
 * @return true si le mot se trouve dans le dictionnaire, false sinon
 * @pre le dictionnaire doit être trié dans l'ordre lexicographique
 */
bool IsWordValid(const WordList& dictionary, const CardList& word);

/*!
 * @brief Vérifie si la collection a est une partie de la collection b,
 *        et que les éléments de a sont dans le même ordre dans a et dans b
 * @param a La liste à chercher
 * @param b La liste dans laquelle chercher
 * @return true si b inclue a et éléments dans le même ordre sinon false
 */
bool IsOrderedSublist(const CardList& a, const CardList& b);

/*!
 * @brief Lit le dictionnaire de mot valides depuis le fichier "ods4.txt"
 * @param[in, out] dictionary La liste de mot qui va contenir les données du fichier
 * @return true si le dictionnaire a pu être lu en entier, false sinon
 */
bool ReadDictionary(WordList& dictionary);

/*!
 * @brief Implémente la commande 'T' du jeu
 * @param[in] params La structure contenant le/les paramètre(s) de la commande récupérée avec ReadPlayerCommand
 * @param[in, out] player Le joueur actuel
 * @param[in, out] exposedCards La pile des cartes exposées
 * @param[in, out] talonCards La pile des cartes invisibles
 */
bool CommandTalon(const CommandParams& params, Player& player, CardStack& exposedCards, CardStack& talonCards);

/*!
 * @brief Implémente la commande 'E' du jeu
 * @param[in] params La structure contenant le/les paramètre(s) de la commande récupérée avec ReadPlayerCommand
 * @param[in, out] player Le joueur actuel
 * @param[in, out] exposedCards La pile des cartes exposées
 */
bool CommandExposed(const CommandParams& params, Player& player, CardStack& exposedCards);

/*!
 * @brief Implémente la commande 'P' du jeu
 * @param[in] params La structure contenant le/les paramètre(s) de la commande récupérée avec ReadPlayerCommand
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
bool CommandPlace(const CommandParams& params, Player& player, WordList& placedWords, const WordList& dictionary);

/*!
 * @brief Implémente la commande 'R' du jeu
 * @param[in] params La structure contenant le/les paramètre(s) de la commande récupérée avec ReadPlayerCommand
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
bool CommandReplace(const CommandParams& params, Player& player, WordList& placedWords, const WordList& dictionary);

/*!
 * @brief Implémente la commande 'C' du jeu
 * @param[in] params La structure contenant le/les paramètre(s) de la commande récupérée avec ReadPlayerCommand
 * @param[in, out] player Le joueur actuel
 * @param[in, out] placedWords La liste des mots placés sur la table
 * @param[in] dictionary Le dictionnaire des mots valides
 */
bool CommandComplete(const CommandParams& params, Player& player, WordList& placedWords, const WordList& dictionary);

#endif //IUT_PROJET2_GAMELOGIC_HPP
