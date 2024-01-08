/*!
 * @file AutoDestructors.hpp
 * @brief Utilisation de l'idiome C++ RAII pour faciliter l'écriture des tests
 *        en évitant de libérer la mémoire dynamique manuellement, et d'assurer la destruction
 *        si un test est faux
 */

#ifndef LEXICON_TESTS_AUTODESTRUCTORS_HPP
#define LEXICON_TESTS_AUTODESTRUCTORS_HPP

#include "../src/Game/Containers/CardList.hpp"
#include "../src/Game/Containers/CardStack.hpp"
#include "../src/Game/Containers/WordList.hpp"
#include "../src/Game/Players.hpp"


struct CardListAuto
{
    CardList cards;

    CardListAuto(size_t cap = 0) : cards(CardListCreate(cap)) {}
    CardListAuto(CardList& other) : cards(other) {}
    CardListAuto(CardList&& other) : cards(other) {}

    ~CardListAuto()
    {
        CardListDestroy(cards);
    }

    operator CardList&()
    {
        return cards;
    }
};

struct CardStackAuto
{
    CardStack cards;

    CardStackAuto(size_t cap = 0) : cards(CardStackCreate(cap)) {}
    CardStackAuto(CardStack& other) : cards(other) {}

    ~CardStackAuto()
    {
        CardStackDestroy(cards);
    }

    operator CardStack&()
    {
        return cards;
    }
};

struct WordListAuto
{
    WordList words;

    WordListAuto(size_t cap = 0) : words(WordListCreate(cap)) {}
    WordListAuto(WordList& other) : words(other) {}

    ~WordListAuto()
    {
        WordListDestroy(words);
    }

    operator WordList&()
    {
        return words;
    }
};

struct PlayerListAuto
{
    PlayerList players;

    PlayerListAuto(size_t cap = 2) : players(PlayerListCreate(cap)) {}
    PlayerListAuto(PlayerList& other) : players(other) {}

    ~PlayerListAuto()
    {
        PlayerListDestroy(players);
    }

    operator PlayerList&()
    {
        return players;
    }
};

#endif //LEXICON_TESTS_AUTODESTRUCTORS_HPP
