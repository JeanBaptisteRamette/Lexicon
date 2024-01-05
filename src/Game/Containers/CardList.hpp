#ifndef LEXICON_CONTAINERS_CARDLIST_HPP
#define LEXICON_CONTAINERS_CARDLIST_HPP


#include <cstddef>
#include "../Definitions.hpp"


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

/*!
 * @brief Vide la liste
 * @param[in, out] cardList La liste à vider
 */
void CardListClear(CardList& cardList);

/*!
 * @brief Trouve l'indice de la première occurrence de la valeur d'une carte
 * @param[in] cardList
 * @param[in] card
 * @param[out] index
 * @return true si la liste contient la valeur carte -> index est donc valide
 *         false si la liste ne contient pas la valeur carte -> index est invalide
 */
bool CardListIndexOf(const CardList& cardList, Card card, size_t& index);

/*!
 * @brief Vérifie si la liste est vide
 * @param[in] cardList La liste pour laquelle vérifier
 * @return true si vide false sinon
 */
bool IsEmpty(const CardList& cardList);

/*!
 * @brief Récupère le nombre d'éléments contenu dans la liste
 * @param[in] cardList La liste pour laquelle on veut la taille
 * @return Le nombre d'éléments
 */
size_t ListSize(const CardList& cardList);

/*!
 * @brief Récupère la carte à un indice donnée dans la liste
 * @param[in] cardList La liste dans laquelle récupérer
 * @param[in] index La position dans la liste
 * @return La carte récupérée
 * @pre index < ListSize(cardList)
 */
Card CardAt(const CardList& cardList, size_t index);

/*!
 * @brief Modifie la carte à l'indice donnée dans la liste
 * @param[in, out] cardList La liste à modifier
 * @param[in] index La position dans la liste de la carte à modifier
 * @param[in] card La nouvelle valeur de la carte à l'indice donnée
 * @pre index < ListSize(cardList)
 */
void SetCardAt(CardList& cardList, size_t index, Card card);

/*!
 * @brief Ajoute une carte à la liste
 * @param[in, out] cardList La liste dans laquelle ajouter
 * @param[in] card La carte à ajouter
 */
void CardListAppend(CardList& cardList, Card card);

/*!
 * @brief Supprime la première occurrence de la carte dans la liste
 * @param[in, out] cardList La liste dans laquelle supprimer
 * @param[in] card La valeur de la carte à supprimer
 */
void CardListRemove(CardList& cardList, Card card);

/*!
 * @brief Supprime de la liste la carte à l'indice donné
 * @param[in, out] cardList La liste dans laquelle supprimer
 * @param[in] index La position de la carte à supprimer
 * @pre index < ListSize(cardList)
 */
void CardListRemoveAt(CardList& cardList, size_t index);

/*!
 * @brief Supprime la dernière carte de la liste
 * @param[in, out] cardList La liste dont on supprime
 * @return La carte supprimée
 * @pre IsEmpty(cardList) == false
 */
Card CardListRemoveLast(CardList& cardList);

/*!
 * @brief Récupère tous les éléments inclus dans a mais pas dans b
 * @param[in] a
 * @param[in] b
 * @return La liste de carte inclues dans a mais pas dans b
 */
CardList CardListDifference(const CardList& a, const CardList& b);

/*!
 * @brief Compare le contenu de deux liste de cartes
 * @param[in] lhs La liste de carte à gauche de l'expression ListeX == ListeY
 * @param[in] rhs La liste de carte à droite de l'expression ListeX == ListeY
 * @return 0 si le contenu est le même, -1 si lhs < rhs, 1 si lhs > rhs
 */
int CardListCompare(const CardList& lhs, const CardList& rhs);

/*!
 *
 * @param cardList
 * @return
 */
Card* CardListBegin(const CardList& cardList);

/*!
 *
 * @param cardList
 * @return
 */
Card* CardListEnd(const CardList& cardList);


#endif //LEXICON_CONTAINERS_CARDLIST_HPP
