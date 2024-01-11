/*!
 * @file CardStack.hpp
 * @brief Définition de l'interface d'une pile de carte
 */

#ifndef LEXICON_CONTAINERS_CARDSTACK_HPP
#define LEXICON_CONTAINERS_CARDSTACK_HPP

#include "../Definitions.hpp"
#include "CardList.hpp"


/*!
 * Structure représentant une pile de carte
 */
struct CardStack
{
    // On utilise simplement une liste pour l'implémentation,
    // à laquelle on ne fait qu'ajouter et supprimer par le haut
    CardList list;
};


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

/*!
 * @brief Vérifie si une pile est vide ou pas
 * @param cardStack La pile
 * @return true si la pile est vide, false sinon
 */
bool IsEmpty(const CardStack& cardStack);

#endif //LEXICON_CONTAINERS_CARDSTACK_HPP
