#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <charconv>
#include <cstring>
#include <algorithm>
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
    std::cout << "(Commandes valides : TEPRC)\n" << std::endl;
}

void DisplayInvalidCommand()
{
    std::cout << "Coup invalide, recommencez" << std::endl;
}

void DisplayInvalidWord()
{
    std::cout << "Mot invalide, vous passez votre tour" << std::endl;
}

void DisplayGameOver()
{
    std::cout << "La partie est finie" << std::endl;
}

void DisplayCardList(const CardList& cardList)
{
    for (size_t i = 0; i < ListSize(cardList); ++i)
        std::cout << CardAt(cardList, i);

    std::cout << std::endl;
}

void DisplayCardListSorted(const CardList& cardList)
{
    // On prend une copie de la liste en paramètre
    // Une fonction d'affichage ne doit pas modifier le paramètre
    CardList copy = CardListCopy(cardList);

    // Trier la liste du début à la fin
    std::sort(
        CardListBegin(copy),
        CardListEnd(copy)
    );

    DisplayCardList(cardList);

    CardListDestroy(copy);
}

void DisplayGameState(const GameData& game)
{
    //
    // Afficher l'identifiant du joueur actuel et la première carte exposée (la pile n'est jamais vide)
    //
    std::cout << "* Joueur " << GetCurrentPlayerId(game.players) << " (" << CardStackPeek(game.exposedCards) << ") ";

    const Player& currentPlayer = GetCurrentPlayer(game.players);

    //
    // Afficher la main du joueur actuel, true pour affichage triée
    //
    DisplayCardListSorted(currentPlayer.cards);

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

    for (size_t i = 0; i < ListSize(players); ++i)
    {
        const Player& player = PlayerAt(players, i);

        //
        // Afficher seulement s'il n'a pas perdu
        //
        if (!player.lost)
            std::cout << "Joueur " << i + 1 << " : " << player.score << " points" << std::endl;
    }
}

bool ReadPlayerCommand(CommandParams& cmd)
{
    std::cout << "> ";

    char input[MAX_COMMAND_LENGTH + 1];

    std::cin >> std::ws;
    std::cin.getline(input, sizeof(input));
    std::istringstream stream(input);

    stream >> cmd.name;

    if (stream.peek() != ' ')
        return false;

    // Ces deux commandes prennent un nombre en plus en paramètre
    if (cmd.name == Command::REPLACE || cmd.name == Command::COMPLETE)
    {
        stream >> cmd.wordIndex;

        if (stream.peek() != ' ')
            return false;

        --cmd.wordIndex;
    }

    // Ces deux commandes prennent seulement une lettre en paramètre
    if (cmd.name == Command::TALON || cmd.name == Command::EXPOSED)
    {
        stream >> cmd.card;
    }
    else
    {
        char cards[MAX_COMMAND_WORD_LENGTH + 1];
        stream >> std::setw(sizeof(cards));
        stream >> cards;

        cmd.cards = CardListCopyString(cards);
    }

    // Vérifier qu'il ne reste pas d'autres caractères sur la ligne
    return (stream >> std::ws).eof();
}


