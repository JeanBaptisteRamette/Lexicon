/*!
 * @file CardStack.cpp
 * @brief Implémentation d'une pile de carte
 */

#include <cassert>
#include "CardStack.hpp"


CardStack CardStackCreate(size_t initialCapacity)
{
    CardStack stack {
        .list = CardListCreate(initialCapacity)
    };

    return stack;
}

void CardStackDestroy(CardStack& cardStack)
{
    CardListDestroy(cardStack.list);
}

Card CardStackPeek(const CardStack& cardStack)
{
    assert(!IsEmpty(cardStack.list));

    return CardAt(cardStack.list, ListSize(cardStack.list) - 1);
}

void CardStackPush(CardStack& cardStack, Card card)
{
    CardListAppend(cardStack.list, card);
}

Card CardStackPop(CardStack& cardStack)
{
    assert(!IsEmpty(cardStack.list));

    return CardListRemoveLast(cardStack.list);
}

bool IsEmpty(const CardStack& cardStack)
{
    return IsEmpty(cardStack.list);
}
