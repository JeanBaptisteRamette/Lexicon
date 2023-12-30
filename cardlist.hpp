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
 * @param[in] buffer chaîne de caractères null-terminated
 * @return CardList de taille strlen(buffer) et contenant les éléments du buffer copiés
 */
CardList CardListCopyString(const char* buffer);

/*!
 * @brief Détruit une liste de caractère allouée dynamiquement
 * @param[in] cardList
 */
void CardListDestroy(CardList& cardList);

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

/*!
 * @brief Compare le contenu de deux liste de cartes
 * @param[in] lhs La liste de carte à gauche de l'expression ListeX == ListeY
 * @param[in] rhs La liste de carte à droite de l'expression ListeX == ListeY
 * @return 0 si le contenu est le même, -1 si lhs < rhs, 1 si lhs > rhs
 */
int CardListCompare(const CardList& lhs, const CardList& rhs);


#endif //IUT_PROJET2_CONTENEURCARTES_HPP
