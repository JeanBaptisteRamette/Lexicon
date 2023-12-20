#ifndef IUT_PROJET2_GAMEINTERFACE_HPP
#define IUT_PROJET2_GAMEINTERFACE_HPP


#include "definitions.hpp"
#include "players.hpp"
#include "wordlist.hpp"
#include "cardlist.hpp"
#include "cardstack.hpp"


void DisplayValidCommands();
void DisplayInvalidCommand();
void DisplayInvalidWord();
void DisplayGameState(const PlayerList& players, const CardStack& exposedCards, const WordList& placedWords);
void DisplayScores(const PlayerList& players);
void DisplayGameOver();

Command GetPlayerCommand();

size_t ReadWordNumber();
Card ReadCard();
CardList ReadCards();


#endif //IUT_PROJET2_GAMEINTERFACE_HPP
