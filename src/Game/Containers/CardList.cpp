/*!
 * @file CardList.cpp
 * @brief Implémentation d'une liste de carte, pouvant représenter la main d'un joueur, un mot placé par un joueur...
 *
 * L'implémentation actuelle repose sur un tableau extensible, l'interface d'utilisation peut tout à fait être reproduite
 * avec une autre structure de donnée comme une liste chaînée.
 */

#include <cassert>
#include <cstring>
#include "CardList.hpp"


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


CardList CardListCreate(size_t initialCapacity)
{
    const CardList cards = {
         .capacity = initialCapacity,
         .count = 0,
         .cards = initialCapacity ? new Card[initialCapacity] : nullptr,
    };

    return cards;
}

void CardListClear(CardList& cardList)
{
    cardList.count = 0;
}

CardList CardListCopy(const CardList& copied)
{
    const size_t count = ListSize(copied);

    CardList cards = CardListCreate(count);

    for (size_t i = 0; i < count; ++i)
        CardListAppend(cards, CardAt(copied, i));

    return cards;
}

CardList CardListCopyString(const char* buffer)
{
    const size_t bufferLength = buffer ? strlen(buffer) : 0;

    CardList cards = CardListCreate(bufferLength);

    for (size_t i = 0; i < bufferLength; ++i)
        CardListAppend(cards, buffer[i]);

    return cards;
}

void CardListDestroy(CardList& cardList)
{
    delete[] cardList.cards;

    cardList.capacity = 0;
    cardList.count = 0;
}

bool CardListIndexOf(const CardList& cardList, Card card, size_t& index)
{
    for (size_t i = 0; i < ListSize(cardList); ++i)
    {
        if (CardAt(cardList, i) == card)
        {
            index = i;
            return true;
        }
    }

    return false;
}

void CardListRemove(CardList& cardList, Card card)
{
    size_t index;

    if (CardListIndexOf(cardList, card, index))
        CardListRemoveAt(cardList, index);
}

bool IsEmpty(const CardList& cardList)
{
    return ListSize(cardList) == 0;
}

size_t ListSize(const CardList& cardList)
{
    return cardList.count;
}

Card CardAt(const CardList& cardList, size_t index)
{
    assert(index < ListSize(cardList));

    return cardList.cards[index];
}

void SetCardAt(CardList& cardList, size_t index, Card card)
{
    assert(index < ListSize(cardList));

    cardList.cards[index] = card;
}

Card CardListRemoveLast(CardList& cardList)
{
    assert(!IsEmpty(cardList));

    const Card backCard = CardAt(cardList, ListSize(cardList) - 1);

    --cardList.count;

    return backCard;
}

void CardListAppend(CardList& cardList, Card card)
{
    // Vérifier s'il est nécessaire de réallouer
    if (cardList.count >= cardList.capacity)
    {
        CardList old = cardList;

        // Augmenter la capacité, le + 1 gère le cas ou la capacité est de 0
        cardList.capacity = (cardList.capacity + 1) * CARD_LIST_CAPACITY_EXTEND;
        cardList.cards = new Card[cardList.capacity];

        // Recopier les anciennes cartes dans la nouvelle mémoire
        for (size_t i = 0; i < old.count; ++i)
            cardList.cards[i] = old.cards[i];

        // Libérer la mémoire qui contenait l'ancien tableau
        CardListDestroy(old);
    }

    // Ajouter la carte à la fin du tableau
    ++cardList.count;
    SetCardAt(cardList, cardList.count - 1, card);
}

void CardListRemoveAt(CardList& cardList, size_t index)
{
    assert(index < ListSize(cardList));

    for (; index < ListSize(cardList) - 1; ++index)
        cardList.cards[index] = cardList.cards[index + 1];

    CardListRemoveLast(cardList);
}

CardList CardListDifference(const CardList& lhs, const CardList& rhs)
{
    CardList diff = CardListCopy(lhs);

    for (size_t i = 0; i < ListSize(rhs); ++i)
    {
        const Card c = CardAt(rhs, i);
        CardListRemove(diff, c);
    }

    return diff;
}

int CardListCompare(const CardList& lhs, const CardList& rhs)
{
    const size_t lhsLength = ListSize(lhs);
    const size_t rhsLength = ListSize(rhs);

    const int ret = strncmp(lhs.cards, rhs.cards, MIN(lhsLength, rhsLength));

    if (ret != 0 || lhsLength == rhsLength)
        return ret;

    return lhsLength < rhsLength ? -1 : 1;
}
