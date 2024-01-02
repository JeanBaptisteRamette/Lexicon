#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <charconv>
#include "Interface.hpp"


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

void DisplayCardList(const CardList& cardList)
{
    for (size_t i = 0; i < ListSize(cardList); ++i)
        std::cout << CardAt(cardList, i);

    std::cout << std::endl;
}

void DisplayGameState(const GameData& game)
{
    //
    // Afficher l'identifiant du joueur actuel et la première carte exposée (la pile n'est jamais vide)
    //
    std::cout << "* Joueur " << GetCurrentPlayerId(game.players) << " (" << CardStackPeek(game.exposedCards) << ") ";

    const Player& currentPlayer = GetCurrentPlayer(game.players);

    //
    // Afficher la main du joueur actuel
    //
    DisplayCardList(currentPlayer.cards);

    //
    // Afficher la liste des mots placés sur la table
    //
    for (size_t i = 0; i < ListSize(game.placedWords); ++i)
    {
        const CardList& word = WordAt(game.placedWords, i);

        std::cout << i + 1 << " - ";

        DisplayCardList(word);
    }
}

void DisplayScores(const PlayerList& players)
{
    std::cout << "Le tour est fini" << std::endl;
    std::cout << "* Scores" << std::endl;

    //
    // Afficher le score total de chaque joueur
    //
    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = PlayerAt(players, i);
        std::cout << "Joueur " << i + 1 << " : " << player.score << " points" << std::endl;
    }
}

bool ReadPlayerCommand(CommandParams& cmd)
{
    std::cout << "> ";

    char input[MAX_COMMAND_LENGTH + 1];

    std::cin >> std::ws;
    std::cin.getline(input, MAX_COMMAND_LENGTH + 1);
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
        char cards[MAX_COMMAND_WORD_LENGTH + 1];
        stream >> std::setw(MAX_COMMAND_WORD_LENGTH + 1);
        stream >> cards;

        cmd.cards = CardListCopyString(cards);
    }

    return (stream >> std::ws).eof();
}

void DisplayGameOver()
{
    std::cout << "La partie est finie" << std::endl;
}

