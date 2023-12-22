#ifndef IUT_PROJET2_CONTENEURCARTES_HPP
#define IUT_PROJET2_CONTENEURCARTES_HPP


#include <cstdint>
#include "definitions.hpp"


enum
{
    CARD_LIST_CAPACITY_EXTEND = 2  // Facteur d'extension par défaut d'une liste de carte
};

struct CardList
{
    size_t capacity;
    size_t count;
    Card* cards;
};


CardList CardListCreate(size_t initialCapacity);
CardList CardListCopy(const CardList& copied);
CardList CardListFromBuffer(const char* buffer, size_t bufferLength);
void CardListDestroy(CardList& cardList);
bool CardListContains(const CardList& cardList, Card card);
bool CardListIndexOf(const CardList& cardList, Card card, size_t& index);
size_t ListSize(const CardList& cardList);
Card CardAt(const CardList& cardList, size_t index);
void SetCardAt(CardList& cardList, size_t index, Card card);
void CardListAppend(CardList& cardList, Card card);
void CardListRemove(CardList& cardList, Card card);
void CardListRemoveAt(CardList& cardList, size_t index);
Card CardListRemoveLast(CardList& cardList);
CardList CardListDifference(const CardList& a, const CardList& b);
int CardListCompare(const CardList& left, const CardList& right);


#endif //IUT_PROJET2_CONTENEURCARTES_HPP
