#include <iostream>
#include <cassert>
#include <iomanip>
#include "gameinterface.hpp"

bool IsCardValid(Card card)
{
    return card >= 'A' && card <= 'Z';
}


void DisplayValidCommands()
{
    std::cout << "(Commandes valides : TEPRC)" << std::endl;
}

void DisplayInvalidCommand()
{
    std::cout << "Coup invalide, recommencez" << std::endl;
}

void DisplayInvalidWord()
{
    std::cout << "Mot invalide, vous passez votre tour" << std::endl;
}

void DisplayGameState(const PlayerList& players, const CardStack& exposedCards, const WordList& placedWords)
{
    std::cout << "* Joueur " << GetCurrentPlayerId(players) + 1 << " (" << CardStackPeek(exposedCards) << ") ";

    const Player& currentPlayer = GetCurrentPlayer(players);

    // TODO: Afficher les cartes du joueur dans l'ordre alphabétique
    for (size_t i = 0; i < ListSize(currentPlayer.cards); ++i)
    {
        const Card card = CardAt(currentPlayer.cards, i);
        std::cout << card;
    }

    std::cout << std::endl;

    for (size_t i = 0; i < ListSize(placedWords); ++i)
    {
        const CardList& word = WordAt(placedWords, i);

        std::cout << i + 1 << " - ";

        for (size_t j = 0; j < ListSize(word); ++j)
            std::cout << CardAt(word, j);

        std::cout << std::endl;
    }
}

void DisplayScores(const PlayerList& players)
{
    std::cout << "Le tour est fini" << std::endl;
    std::cout << "* Scores" << std::endl;

    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = GetPlayerById(players, i);

        std::cout << "Joueur " << i + 1 << " : " << player.score << "points" << std::endl;
    }
}

Command GetPlayerCommand()
{
    Command c;
    std::cin >> c;
    return c;
}

size_t ReadWordNumber()
{
    size_t index;
    std::cin >> index;
    return index;
}

Card ReadCard()
{
    char c;
    std::cin >> c;
    return c;
}

CardList ReadCards()
{
    Card input[CARDS_COUNT_PLAYER + 1];

    std::cin >> std::setw(CARDS_COUNT_PLAYER + 1);
    std::cin >> input;

    return CardListFromBuffer(input, strlen(input));
}










