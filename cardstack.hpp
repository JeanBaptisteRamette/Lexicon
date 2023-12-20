#ifndef IUT_PROJET2_CARDSTACK_HPP
#define IUT_PROJET2_CARDSTACK_HPP

#include "definitions.hpp"
#include "cardlist.hpp"

struct CardStack
{
    CardList list;
};


CardStack CardStackFromCardList(const CardList& cardList);
CardStack CardStackCreate(size_t initialCapacity);
void CardStackDestroy(CardStack& cardStack);

Card CardStackPeek(const CardStack& cardStack);
void CardStackPush(CardStack& cardStack, Card card);
Card CardStackPop(CardStack& cardStack);

#endif //IUT_PROJET2_CARDSTACK_HPP
