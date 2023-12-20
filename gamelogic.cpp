#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "gamelogic.hpp"
#include "definitions.hpp"
#include "gameinterface.hpp"

#include <string.h>

CardList CreateGameCards()
{
    // Allouer le gameCards de carte
    CardList gameCards = CardListCreate(CARDS_COUNT_GAME);

    unsigned int cards_quantity[CARDS_COUNT_VALUES] = {
            2, 2, 2, 2, 5, 1, 2, 2, 4,
            1, 1, 2, 1, 3, 2, 1, 1, 3,
            3, 3, 3, 1, 1, 1, 1, 1
    };

    // Remplir le paquet de carte
    for (Card card = 'A'; card <= 'Z'; ++card)
        while (cards_quantity[card - 'A']--)
            CardListAppend(gameCards, card);

    return gameCards;
}

void ShuffleCards(CardList& cards)
{
    srand(time(nullptr));

    for (size_t i = 0; i < ListSize(cards); ++i)
    {
        const size_t j = rand() % ListSize(cards);

        const Card c = CardAt(cards, i);

        SetCardAt(cards, i, CardAt(cards, j));
        SetCardAt(cards, j, c);
    }
}

WordList ReadDictionary()
{
    WordList dictionary = WordListCreate(DICTIONARY_WORD_COUNT);

    // Le fichier est fermé automatiquement à la fin de la fonction
    std::ifstream inputFile(DICTIONARY_PATH);

    if (!inputFile)
        return dictionary;

    char buffer[DICTIONARY_MAX_WORD_SIZE + 1];

    do
    {
        inputFile >> std::setw(DICTIONARY_MAX_WORD_SIZE + 1);
        inputFile >> buffer;

        const size_t length = strlen(buffer);

        if (length > 0)
        {
            const CardList word = CardListFromBuffer(buffer, length);
            WordListAppend(dictionary, word);
        }

    } while (inputFile);

    return dictionary;
}

void DistributeCards(PlayerList& players, CardList& cards)
{
    // Mélanger les cartes avant de les distribuer
    ShuffleCards(cards);

    for (size_t i = 0; i < ListSize(players); ++i)
    {
        Player& player = GetPlayerById(players, i);

        for (size_t j = 0; j < CARDS_COUNT_PLAYER; ++j)
        {
            const Card card = CardListRemoveLast(cards);
            CardListAppend(player.cards, card);
        }
    }
}

void CommandTalon(Player& player, CardStack& exposedCards, CardStack& talonCards)
{
    const Card card = ReadCard();

    if (!CardListContains(player.cards, card))
        return;

    // Supprimer la carte de la main du joueur
    CardListRemove(player.cards, card);

    // La carte correspondante est placée au-dessus des cartes exposées
    CardStackPush(exposedCards, card);

    // La première carte du talon est ramassée par le joueur.
    const Card popped = CardStackPop(talonCards);
    CardListAppend(player.cards, popped);
}

void CommandExposed(Player& player, CardStack& exposedCards)
{
    const Card card = ReadCard();

    size_t index;

    if (!CardListIndexOf(player.cards, card, index))
        return;

    const Card popped = CardStackPop(exposedCards);

    SetCardAt(player.cards, index, popped);

    CardStackPush(exposedCards, card);
}

bool HasCards(const Player& player, const CardList& cards)
{
    // FIXME: player.cards must be sorted
    //        cards        must be sorted

    int occurrences[CARDS_COUNT_VALUES] = { 0 };

    for (size_t i = 0; i < ListSize(player.cards); ++i)
    {
        const Card letter = CardAt(player.cards, i);
        ++occurrences[letter - 'A'];
    }

    for (size_t i = 0; i < ListSize(cards); ++i)
    {
        const Card letter = CardAt(cards, i);

        if (--occurrences[letter - 'A'] < 0)
            return false;
    }

    return true;
}

bool IsWordValid(const WordList& dictionary, const CardList& word)
{
    size_t lowerBound = 0;
    size_t upperBound = ListSize(dictionary) - 1;

    while (lowerBound <= upperBound)
    {
        const size_t middle = lowerBound + (upperBound - lowerBound) / 2;
        const int ret = CardListCompare(word, WordAt(dictionary, middle));

        if (ret == 0)
            return true;
        else if (ret == -1)
            upperBound = middle - 1;
        else
            lowerBound = middle + 1;
    }

    return false;
}

void CommandPlace(Player& player, WordList& placedWords, const WordList& dictionary)
{
    CardList word = ReadCards();

    // Vérifier que le mot peut être formé par le joueur et que le mot existe
    if (!HasCards(player, word) || !IsWordValid(dictionary, word))
    {
        CardListDestroy(word);
        return;
    }

    // Supprimer les cartes utilisées de la main du joueur
    for (size_t i = 0; i < ListSize(word); ++i)
        CardListRemove(player.cards, CardAt(word, i));

    WordListAppend(placedWords, word);
}

void CommandReplace(Player& player, WordList& placedWords, const WordList& dictionary)
{
    const size_t wordIndex = ReadWordNumber() - 1;

    if (wordIndex >= ListSize(placedWords))
        return;

    CardList& oldWord = WordAt(placedWords, wordIndex);
    CardList  newWord = ReadCards();

    if (ListSize(oldWord) != ListSize(newWord))
    {
        CardListDestroy(newWord);
        return;
    }

    CardList replacedCards = CardListCreate(ListSize(oldWord));
    CardList replacerCards = CardListCreate(ListSize(newWord));

    for (size_t i = 0; i < ListSize(oldWord); ++i)
    {
        const Card a = CardAt(oldWord, i);
        const Card b = CardAt(newWord, i);

        if (a != b)
        {
            CardListAppend(replacedCards, a);
            CardListAppend(replacerCards, b);
        }
    }

    if (HasCards(player, replacerCards) && IsWordValid(dictionary, newWord))
    {
        SetWordAt(placedWords, wordIndex, newWord);

        for (size_t i = 0; i < ListSize(replacerCards); ++i)
        {
            CardListRemove(player.cards, CardAt(replacerCards, i));
            CardListAppend(player.cards, CardAt(replacedCards, i));
        }
    }
    else
        CardListDestroy(newWord);

    CardListDestroy(replacedCards);
    CardListDestroy(replacerCards);
}

void CommandComplete(Player& player, WordList& placedWords, const WordList& dictionary) {}
















