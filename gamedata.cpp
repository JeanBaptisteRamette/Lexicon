#include <iostream>
#include "gamelogic.hpp"
#include "gamedata.hpp"


bool InitGameData(GameData& game, unsigned int playerCount)
{
    game.players = PlayerListCreate(playerCount);

    CardList gameCards = CreateGameCards();
    DistributeCards(game.players, gameCards);

    CardStackAssignList(game.talonCards, gameCards);
    game.exposedCards = CardStackCreate();

    CardStackPush(game.exposedCards, CardStackPop(game.talonCards));

    game.placedWords = WordListCreate();

    if (!ReadDictionary(game.dictionary))
    {
        std::cerr << "Erreur lors de la lecture du dictionnaire de mots" << std::endl;
        return false;
    }

    return true;
}

void DestroyGameData(GameData& game)
{
    PlayerListDestroy(game.players);
    CardStackDestroy(game.talonCards);
    CardStackDestroy(game.exposedCards);
    WordListDestroy(game.placedWords);
    WordListDestroy(game.dictionary);
}
