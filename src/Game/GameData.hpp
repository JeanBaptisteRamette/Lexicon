#ifndef LEXICON_GAMEDATA_HPP
#define LEXICON_GAMEDATA_HPP

#include "Players.hpp"
#include "Containers/CardList.hpp"
#include "Containers/WordList.hpp"
#include "Containers/CardStack.hpp"


struct GameData
{
    PlayerList players;
    CardStack talonCards;
    CardStack exposedCards;

    WordList placedWords;
    WordList dictionary;
};


/*!
 * @brief Initialise les cartes du jeu
 * @param game Structure contenant les cartes du jeu
 * @note Si la fonction est appelée plusieurs fois désallouer les conteneurs avant l'appel à cette
 *       fonction pour éviter une fuite mémoire
 */
void GameCardsInit(GameData& game);

/*!
 * @brief Désalloue les cartes du jeu alloué par GameCardsInit
 * @param game
 */
void GameCardsDestroy(GameData& game);

/*!
 * @brief Distribue les cartes aux joueurs, place le reste sur le talon, et place la première carte
 *        sur la pile des cartes exposées
 * @param game Structure contenant les cartes du jeu
 */
void GameCardsSetup(GameData& game);

/*!
 * @brief Alloue les données du jeu et les initialise
 * @param[in, out] game Structure contenant les données
 * @param[in] playerCount Nombre de joueur de la partie
 * @return
 */
bool InitGameData(GameData& game, unsigned int playerCount);

/*!
 * @brief Désalloue les données du jeu alloué par InitGameData
 * @param[in] game
 */
void DestroyGameData(GameData& game);


#endif //LEXICON_GAMEDATA_HPP
