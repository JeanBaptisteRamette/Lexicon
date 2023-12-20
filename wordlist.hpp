#ifndef IUT_PROJET2_WORDLIST_HPP
#define IUT_PROJET2_WORDLIST_HPP

#include "cardlist.hpp"

enum
{
    WORD_LIST_CAPACITY_EXTEND = 2  // facteur d'extension par défaut d'une liste de mot
};

struct WordList
{
    size_t capacity;
    size_t count;
    CardList* words;
};


WordList WordListCreate(size_t initialCapacity);
void WordListDestroy(WordList& wordList);
size_t ListSize(const WordList& wordList);
CardList& WordAt(const WordList& wordList, size_t index);
void SetWordAt(WordList& wordList, size_t index, CardList word);
void WordListAppend(WordList& wordList, CardList word);





#endif //IUT_PROJET2_WORDLIST_HPP
