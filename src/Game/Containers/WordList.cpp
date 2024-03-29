/*!
 * @file WordList.cpp
 * @brief Implémentation d'une liste de mot
 */

#include <cassert>
#include "WordList.hpp"


WordList WordListCreate(size_t initialCapacity)
{
    // Alloué la liste de mots avec une capacité nulle ou pas
    const WordList words = {
            .capacity = initialCapacity,
            .count = 0,
            .words = initialCapacity ? new CardList[initialCapacity] : nullptr,
    };

    return words;
}

void WordListDestroy(WordList& wordList)
{
    // Détruire tous les mots présents dans la liste avant de détruire la liste et perdre les pointeurs
    for (size_t i = 0; i < ListSize(wordList); ++i)
    {
        CardList& word = WordAt(wordList, i);
        CardListDestroy(word);
    }

    // Détruire la liste
    delete[] wordList.words;
}

size_t ListSize(const WordList& wordList)
{
    return wordList.count;
}

CardList& WordAt(const WordList& wordList, size_t index)
{
    assert(index < ListSize(wordList));

    return wordList.words[index];
}

void SetWordAt(WordList& wordList, size_t index, const CardList& word)
{
    assert(index < ListSize(wordList));

    CardListDestroy(wordList.words[index]);

    wordList.words[index] = word;
}

void WordListAppend(WordList& wordList, const CardList& word)
{
    // Vérifier s'il est nécessaire de réallouer
    if (wordList.count >= wordList.capacity)
    {
        const CardList* old = wordList.words;

        wordList.capacity = (wordList.capacity + 1) * WORD_LIST_CAPACITY_EXTEND;
        wordList.words = new CardList[wordList.capacity];

        if (old)
        {
            for (size_t i = 0; i < ListSize(wordList); ++i)
                wordList.words[i] = old[i];

            // Libérer la mémoire qui contenait l'ancien tableau (pas celle qui contient les éléments des listes)
            delete[] old;
        }
    }

    // Ajouter le mot à la fin du tableau
    wordList.words[wordList.count] = word;
    ++wordList.count;
}
