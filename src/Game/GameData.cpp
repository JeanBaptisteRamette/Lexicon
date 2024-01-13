/*!
 * @file GameData.cpp
 * @brief Implémentation des fonctions liés aux données du jeu
 */

#include <fstream>
#include "GameData.hpp"
#include "Logic.hpp"
#include "Interface.hpp"


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

    // Retourne la première carte du talon
    CardStackPush(game.exposedCards, CardStackPop(game.talonCards));
}

bool ReadDictionary(WordList& dictionary)
{
    // 1. Réserver une liste de mots pouvant contenir jusqu'à DICTIONARY_WORD_COUNT avant réallocation
    dictionary = WordListCreate(DICTIONARY_WORD_COUNT);

    // 2. Ouverture du fichier, il sera fermé automatiquement au retour de la fonction
    std::ifstream inputFile(DICTIONARY_PATH);

    char buffer[DICTIONARY_MAX_WORD_SIZE + 1];

    // 3. Lire tant que le flux est valide
    while (inputFile.getline(buffer, sizeof(buffer)))
    {
        const CardList word = CardListCopyString(buffer);
        WordListAppend(dictionary, word);
    }

    // 4. Vérifier qu'on a bien lu DICTIONARY_WORD_COUNT mots
    return ListSize(dictionary) == DICTIONARY_WORD_COUNT;
}

bool InitGameData(GameData& game, unsigned int playerCount)
{
    game.players = PlayerListCreate(playerCount);

    GameCardsInit(game);
    GameCardsSetup(game);

    if (!ReadDictionary(game.dictionary))
    {
        DisplayDictionaryReadError();
        return false;
    }

    return true;
}

void DestroyGameData(GameData& game)
{
    WordListDestroy(game.dictionary);
    GameCardsDestroy(game);
    PlayerListDestroy(game.players);
}
