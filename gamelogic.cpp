#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "gamelogic.hpp"
#include "definitions.hpp"
#include "gameinterface.hpp"


CardList CreateGameCards()
{
    // Allouer le paquet de carte
    CardList gameCards = CardListCreate(CARDS_COUNT_GAME);

    unsigned int quantities[CARDS_COUNT_VALUES] = {
            2, 2, 2, 2, 5, 1, 2, 2, 4,
            1, 1, 2, 1, 3, 2, 1, 1, 3,
            3, 3, 3, 1, 1, 1, 1, 1
    };

    // Remplir le paquet de carte
    for (Card card = 'A'; card <= 'Z'; ++card)
        while (quantities[card - 'A']--)
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

bool IsGameOver(const PlayerList& players)
{
    size_t activePlayerCount = 0;

    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = GetPlayerById(players, i);

        if (!player.lost)
            ++activePlayerCount;
    }

    return activePlayerCount < MIN_PLAYER_COUNT;
}

void UpdateLosers(PlayerList& players)
{
    for (size_t i = 0; i < ListSize(players); ++i)
    {
        Player& player = GetPlayerById(players, i);

        if (GetTotalScore(player) > MAXIMUM_QUALIFIED_SCORE)
            player.lost = true;
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

void CommandTalon(const Command& cmd, Player& player, CardStack& exposedCards, CardStack& talonCards)
{
    const Card card = cmd.card;

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

void CommandExposed(const Command& cmd, Player& player, CardStack& exposedCards)
{
    const Card card = cmd.card;

    size_t index;

    if (!CardListIndexOf(player.cards, card, index))
        return;

    const Card popped = CardStackPop(exposedCards);

    SetCardAt(player.cards, index, popped);

    CardStackPush(exposedCards, card);
}

bool HasCards(const Player& player, const CardList& cards)
{
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

void CommandPlace(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary)
{
    CardList word = cmd.cards;

    // Vérifier que le mot peut être formé par le joueur et que le mot existe
    if (!HasCards(player, word) || !IsWordValid(dictionary, word))
    {
        ApplyScorePenalty(player, INVALID_WORD_PENALTY);
        DisplayInvalidWord();
        CardListDestroy(word);
        return;
    }

    // Supprimer les cartes utilisées de la main du joueur
    for (size_t i = 0; i < ListSize(word); ++i)
        CardListRemove(player.cards, CardAt(word, i));

    WordListAppend(placedWords, word);
}

void CommandReplace(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary)
{
    const size_t wordIndex = cmd.wordIndex;

    if (wordIndex >= ListSize(placedWords))
        return;

    CardList& oldWord = WordAt(placedWords, wordIndex);
    CardList  newWord = cmd.cards;

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
    {
        ApplyScorePenalty(player, INVALID_WORD_PENALTY);
        DisplayInvalidWord();
        CardListDestroy(newWord);
    }

    CardListDestroy(replacedCards);
    CardListDestroy(replacerCards);
}

bool IsOrderedSublist(const CardList& a, const CardList& b)
{
    // assert(!IsEmpty(b));

    size_t j = 0;

    for (size_t i = 0; i < ListSize(a); ++i)
    {
        while (CardAt(b, j) != CardAt(a, i))
        {
            ++j;

            if (j >= ListSize(b))
                return false;
        }
    }

    return true;
}

void CommandComplete(const Command& cmd, Player& player, WordList& placedWords, const WordList& dictionary)
{
    const size_t wordIndex = cmd.wordIndex;

    if (wordIndex >= ListSize(placedWords))
        return;

    CardList& oldWord = WordAt(placedWords, wordIndex);
    CardList  newWord = cmd.cards;

    // TODO: Improve deallocation of var newWord
    if (IsOrderedSublist(oldWord, newWord))
    {
        CardList diff = CardListDifference(newWord, oldWord);

        // Vérifier que le mot peut être placé par le joueur
        if (HasCards(player, diff))
        {
            SetWordAt(placedWords, wordIndex, newWord);

            // Supprimer les cartes utilisées par le joueur de sa main
            for (size_t i = 0; i < ListSize(diff); ++i)
            {
                const Card c = CardAt(diff, i);
                CardListRemove(player.cards, c);
            }
        } else
            CardListDestroy(newWord);

        CardListDestroy(diff);
    } else
        CardListDestroy(newWord);
}

















