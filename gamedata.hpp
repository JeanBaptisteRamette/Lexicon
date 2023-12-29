#ifndef IUT_PROJET2_GAMEDATA_HPP
#define IUT_PROJET2_GAMEDATA_HPP

#include "players.hpp"
#include "cardlist.hpp"
#include "wordlist.hpp"
#include "cardstack.hpp"


struct GameData
{
    PlayerList players;
    CardStack talonCards;
    CardStack exposedCards;

    WordList placedWords;
    WordList dictionary;
};


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


#endif //IUT_PROJET2_GAMEDATA_HPP
