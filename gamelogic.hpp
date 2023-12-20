#ifndef IUT_PROJET2_GAMELOGIC_HPP
#define IUT_PROJET2_GAMELOGIC_HPP

#include "cardlist.hpp"
#include "wordlist.hpp"
#include "cardstack.hpp"
#include "players.hpp"


CardList CreateGameCards();

void ShuffleCards(CardList& cards);
void DistributeCards(PlayerList& players, CardList& cards);

WordList ReadDictionary();

void CommandTalon(Player& player, CardStack& exposedCards, CardStack& talonCards);
void CommandExposed(Player& player, CardStack& exposedCards);
void CommandPlace(Player& player, WordList& placedWords, const WordList& dictionary);
void CommandReplace(Player& player, WordList& placedWords, const WordList& dictionary);
void CommandComplete(Player& player, WordList& placedWords, const WordList& dictionary);

#endif //IUT_PROJET2_GAMELOGIC_HPP
