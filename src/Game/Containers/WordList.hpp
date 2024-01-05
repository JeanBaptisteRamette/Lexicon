#ifndef LEXICON_CONTAINERS_WORDLIST_HPP
#define LEXICON_CONTAINERS_WORDLIST_HPP

#include "CardList.hpp"

enum
{
    WORD_LIST_CAPACITY_EXTEND = 2  // facteur d'extension par défaut d'une liste de mot
};

struct WordList
{
    size_t capacity;
    size_t count;
    CardList* words;
};


/*!
 * @brief Créer une liste de mot, c'est à dire de CardList
 * @param[in] initialCapacity la capacité initiale de la liste, par défaut à 0, l'ajout d'élément fonctionnera aussi
 * @return La liste de mot pouvant contenir initialCapacity mot, désallouer avec WordListDestroy
 */
WordList WordListCreate(size_t initialCapacity = 0);

/*!
 * @brief Désalloue la liste de mot, et les mots qui sont eux aussi alloués dynamiquement par WordListCreate
 * @param[in, out] wordList La liste de mot à désallouer
 */
void WordListDestroy(WordList& wordList);

/*!
 * @brief Retourne le nombre de mot dans la liste
 * @param[in] wordList La liste
 * @return Le nombre de mot dans la liste
 */
size_t ListSize(const WordList& wordList);

/*!
 * @brief Retourne une référence vers un mot de la liste
 * @param[in] wordList La liste de mot
 * @param[in] index Indice du mot que l'on veut récupérer
 * @return Référence vers le mot à l'indice index
 * @pre index < ListSize(wordList)
 */
CardList& WordAt(const WordList& wordList, size_t index);

/*!
 * @brief Modifie la valeur le mot à l'indice donné
 * @param[in, out] wordList La liste de mot
 * @param[in] index L'indice du mot à modifié
 * @param[in] word La nouvelle valeur du mot
 * @pre index < ListSize(wordList)
 */
void SetWordAt(WordList& wordList, size_t index, const CardList& word);

/*!
 * @brief Ajoute un mot dans la liste
 * @param[in, out] wordList La liste dans laquelle ajouter
 * @param[in] word Le mot à ajouter
 */
void WordListAppend(WordList& wordList, const CardList& word);




#endif //LEXICON_CONTAINERS_WORDLIST_HPP
