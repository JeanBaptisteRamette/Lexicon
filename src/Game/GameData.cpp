#include <iostream>
#include "Logic.hpp"
#include "GameData.hpp"

void GameCardsInit(GameData& game)
{
    game.talonCards = CreateGameCards();
    game.exposedCards = CardStackCreate();
    game.placedWords = WordListCreate();
}

void GameCardsDestroy(GameData& game)
{
    CardStackDestroy(game.talonCards);
    CardStackDestroy(game.exposedCards);
    WordListDestroy(game.placedWords);
}

void GameCardsSetup(GameData& game)
{
    DistributeCards(game.players, game.talonCards);
    CardStackPush(game.exposedCards, CardStackPop(game.talonCards));
}

bool InitGameData(GameData& game, unsigned int playerCount)
{
    game.players = PlayerListCreate(playerCount);

    GameCardsInit(game);
    GameCardsSetup(game);

    if (!ReadDictionary(game.dictionary))
    {
        std::cerr << "Erreur lors de la lecture du dictionnaire de mots" << std::endl;
        return false;
    }

    return true;
}

void DestroyGameData(GameData& game)
{
    GameCardsDestroy(game);

    PlayerListDestroy(game.players);
    WordListDestroy(game.dictionary);
}
