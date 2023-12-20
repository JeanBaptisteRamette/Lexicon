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
    std::cout << "(Commandes valides : TEPRC)\n\n";
}

void DisplayInvalidCommand()
{
    std::cout << "Coup invalide, recommencez\n";
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

    std::cout << '\n';

    for (size_t i = 0; i < ListSize(placedWords); ++i)
    {
        const CardList& word = WordAt(placedWords, i);

        std::cout << i + 1 << " - ";

        for (size_t j = 0; j < ListSize(word); ++j)
            std::cout << CardAt(word, j);

        std::cout << '\n';
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










