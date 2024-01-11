/*!
 * @file Interface.cpp
 * @brief Implémentation de l'interface du jeu
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <charconv>
#include <cstring>
#include <algorithm>
#include "Interface.hpp"


unsigned int ReadPlayerCount(int argc, const char* argv[])
{
    ++argv;
    --argc;

    if (!argc)
    {
        std::cerr << "Nombre de joueurs manquant" << std::endl;
        return 0;
    }

    const char* beg = *argv;
    const char* end = *argv + strlen(*argv);

    unsigned int playerCount;

    // Essaye de convertir une chaîne de caractère en entier
    const std::from_chars_result result = std::from_chars(beg, end, playerCount);

    if (result.ec != std::errc() || playerCount < MIN_PLAYER_COUNT || playerCount > MAX_PLAYER_COUNT)
    {
        std::cerr << "Nombre de joueurs invalide" << std::endl;
        return 0;
    }

    return playerCount;
}

void DisplayDictionaryReadError()
{
    std::cerr << "Erreur lors de la lecture du dictionnaire" << std::endl;
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

    DisplayCardList(copy);

    // Détruire la copie
    CardListDestroy(copy);
}

void DisplayGameState(const GameData& game)
{
    // Afficher l'identifiant du joueur actuel et la première carte exposée (la pile n'est jamais vide)
    std::cout << "* Joueur " << GetCurrentPlayerId(game.players) << " (" << CardStackPeek(game.exposedCards) << ") ";

    const Player& currentPlayer = GetCurrentPlayer(game.players);

    // Afficher la main du joueur actuel
    DisplayCardListSorted(currentPlayer.cards);

    // Afficher la liste des mots placés sur la table
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

        // Seulement afficher les scores des joueurs actifs
        if (!player.lost)
            std::cout << "Joueur " << i + 1 << " : " << player.score << " points" << std::endl;
    }
}

std::istringstream ReadCommandAsStream()
{
    char input[MAX_COMMAND_LENGTH + 1];

    // Lire l'entrée sur une seule ligne, puis utiliser std::istringstream facilitant la lecture
    std::cin >> std::ws;
    std::cin.getline(input, sizeof(input));
    std::istringstream stream(input);

    // Vérifier s'il y a trop de caractères saisit
    if (std::cin.fail())
    {
        // Remettre dans un état valide le stream
        std::cin.clear();

        // Ignorer les caractères en trop sur la ligne
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return stream;
}

bool ReadCommandFromStream(Command& cmd, std::istringstream& stream)
{
    // Lire le nom de la commande
    if (!(stream >> cmd.name) || stream.peek() != ' ')
        return false;

    // Lire une seule carte pour 'T' et 'E'
    if (cmd.name == Commands::TALON || cmd.name == Commands::EXPOSED)
    {
        stream >> cmd.card;

        // Vérifier que le stream ne contient plus de caractères
        return (stream >> std::ws).eof();
    }

    // Lire un entier pour 'R' et 'C'
    if (cmd.name == Commands::REPLACE || cmd.name == Commands::COMPLETE)
    {
        if (!(stream >> cmd.wordIndex) || stream.peek() != ' ')
            return false;

        --cmd.wordIndex;
    }

    // Lire un mot pour 'R', 'C', et 'P'
    char cards[MAX_COMMAND_WORD_LENGTH + 1];
    stream >> std::setw(sizeof(cards));
    stream >> cards;

    if (!(stream >> std::ws).eof())
        return false;

    cmd.cards = CardListCopyString(cards);
    return true;
}

bool ReadPlayerCommand(Command& cmd)
{
    std::cout << "> ";

    std::istringstream stream = ReadCommandAsStream();

    return ReadCommandFromStream(cmd, stream);
}


