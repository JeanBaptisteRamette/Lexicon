#ifndef IUT_PROJET2_CARDSTACK_HPP
#define IUT_PROJET2_CARDSTACK_HPP

#include "definitions.hpp"
#include "cardlist.hpp"

struct CardStack
{
    CardList list;
};


/*!
 * @brief Créer une pile de carte en copiant les éléments d'une liste de carte
 * @param[in] cardList La liste de carte à copier dans la pile
 * @return La pile de carte
 */
CardStack CardStackFromCardList(const CardList& cardList);

/*!
 * @brief Créer une pile de carte vide
 * @param[in] initialCapacity Capacité initiale de la pile, l'ajout pourra être fait même avec une capacité de 0
 * @return La pile de carte
 */
CardStack CardStackCreate(size_t initialCapacity = 0);

/*!
 * @brief Désalloue la pile de carte
 * @param[in, out] cardStack La pile de carte à désalloué
 */
void CardStackDestroy(CardStack& cardStack);

/*!
 * @brief Lit la carte au sommet de la pile, sans la dépiler
 * @param[in] cardStack La pile
 * @return La carte au sommet de la pile
 */
Card CardStackPeek(const CardStack& cardStack);

/*!
 * @brief Ajoute une carte au sommet de la pile
 * @param[in, out] cardStack La pile sur laquelle ajouter
 * @param[in] card La carte ajoutée
 */
void CardStackPush(CardStack& cardStack, Card card);

/*!
 * @brief Supprime la carte au sommet de la pile
 * @param[in, out] cardStack La pile dont on enlève la carte
 * @return La carte dépilée
 */
Card CardStackPop(CardStack& cardStack);

#endif //IUT_PROJET2_CARDSTACK_HPP
