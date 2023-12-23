#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
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
        std::cout << "Joueur " << i + 1 << " : " << GetTotalScore(player) << " points" << std::endl;
    }
}

bool ReadPlayerCommand(Command& cmd)
{
    char input[MAX_COMMAND_LENGTH];

    std::cin >> std::ws;
    std::cin.getline(input, MAX_COMMAND_LENGTH);
    std::istringstream stream(input);

    stream >> cmd.name;

    if (stream.peek() != ' ')
        return false;

    if (cmd.name == Commands::REPLACE || cmd.name == Commands::COMPLETE)
    {
        stream >> cmd.wordIndex;

        if (stream.peek() != ' ')
            return false;

        --cmd.wordIndex;
    }

    if (cmd.name == Commands::TALON || cmd.name == Commands::EXPOSED)
    {
        stream >> cmd.card;
        stream >> std::ws;

        return stream.eof();
    } else
    {
        char cards[MAX_COMMAND_WORD_LENGTH];
        stream >> std::setw(MAX_COMMAND_WORD_LENGTH);
        stream >> cards;

        cmd.cards = CardListFromBuffer(cards, strlen(cards));
    }

    return true;
}

void DisplayGameOver()
{
    std::cout << "La partie est finie" << std::endl;
}

