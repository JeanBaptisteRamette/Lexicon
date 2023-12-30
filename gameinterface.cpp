#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <charconv>
#include "gameinterface.hpp"


unsigned int ReadPlayerCount(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Nombre de joueurs manquant" << std::endl;
        return 0;
    }

    ++argv;

    const char* beg = *argv;
    const char* end = *argv + strlen(*argv);

    unsigned int playerCount;
    const std::from_chars_result result = std::from_chars(beg, end, playerCount);

    if (result.ec != std::errc() || playerCount < MIN_PLAYER_COUNT || playerCount > MAX_PLAYER_COUNT)
    {
        std::cerr << "Nombre de joueurs invalide" << std::endl;
        return 0;
    }

    return playerCount;
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

void DisplayGameState(const GameData& game)
{
    std::cout << "* Joueur " << GetCurrentPlayerId(game.players) + 1 << " (" << CardStackPeek(game.exposedCards) << ") ";

    const Player& currentPlayer = GetCurrentPlayer(game.players);

    for (size_t i = 0; i < ListSize(currentPlayer.cards); ++i)
    {
        const Card card = CardAt(currentPlayer.cards, i);
        std::cout << card;
    }

    std::cout << std::endl;

    for (size_t i = 0; i < ListSize(game.placedWords); ++i)
    {
        const CardList& word = WordAt(game.placedWords, i);

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
        const Player& player = PlayerAt(players, i);
        std::cout << "Joueur " << i + 1 << " : " << GetTotalScore(player) << " points" << std::endl;
    }
}

bool ReadPlayerCommand(CommandParams& cmd)
{
    std::cout << "> ";

    char input[MAX_COMMAND_LENGTH];

    std::cin >> std::ws;
    std::cin.getline(input, MAX_COMMAND_LENGTH);
    std::istringstream stream(input);

    stream >> cmd.name;

    if (stream.peek() != ' ')
        return false;

    if (cmd.name == Command::REPLACE || cmd.name == Command::COMPLETE)
    {
        stream >> cmd.wordIndex;

        if (stream.peek() != ' ')
            return false;

        --cmd.wordIndex;
    }

    if (cmd.name == Command::TALON || cmd.name == Command::EXPOSED)
    {
        stream >> cmd.card;
    } else
    {
        char cards[MAX_COMMAND_WORD_LENGTH];
        stream >> std::setw(MAX_COMMAND_WORD_LENGTH);
        stream >> cards;

        cmd.cards = CardListCopyString(cards);
    }

    return (stream >> std::ws).eof();
}

void DisplayGameOver()
{
    std::cout << "La partie est finie" << std::endl;
}

