#include <cassert>
#include "cardstack.hpp"


CardStack CardStackFromCardList(const CardList& cardList)
{
    CardStack stack = {
            .list = CardListCopy(cardList)
    };

    return stack;
}

CardStack CardStackCreate(size_t initialCapacity)
{
    CardStack stack;

    stack.list = CardListCreate(initialCapacity);

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
