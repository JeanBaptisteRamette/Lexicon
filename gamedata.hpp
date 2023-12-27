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


bool InitGameData(GameData& game, unsigned int playerCount);

void DestroyGameData(GameData& game);


#endif //IUT_PROJET2_GAMEDATA_HPP