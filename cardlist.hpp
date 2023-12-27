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


/*!
 * @brief Créer une liste de carte
 * @param[in] initialCapacity capacité initiale de la liste, 0 par défaut
 *            l'ajout d'élément pourra être fait si la capacité est nulle.
 * @return La liste de cartes vide
 */
CardList CardListCreate(size_t initialCapacity = 0);

/*!
 * @brief Copie les éléments d'une liste de carte
 * @param[in] copied liste de carte à copier
 * @return Une copie de la liste
 */
CardList CardListCopy(const CardList& copied);

/*!
 * @brief Créer une liste de carte à partir d'un buffer
 * @param[in] buffer Pointeur vers le début du buffer
 * @param[in] bufferLength Nombre d'éléments du buffer à copier
 * @return CardList de taille bufferLength et contenant les éléments du buffer copiés
 */
CardList CardListFromBuffer(const char* buffer, size_t bufferLength);

/*!
 * @brief Détruit une liste de caractère allouée dynamiquement
 * @param[in] cardList
 */
void CardListDestroy(CardList& cardList);

bool CardListContains(const CardList& cardList, Card card);
bool CardListIndexOf(const CardList& cardList, Card card, size_t& index);
bool IsEmpty(const CardList& cardList);
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
