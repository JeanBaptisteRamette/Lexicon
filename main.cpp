#include <iostream>
#include <charconv>
#include "gameinterface.hpp"
#include "definitions.hpp"
#include "gamelogic.hpp"
#include "players.hpp"
#include "cardstack.hpp"
#include "cardlist.hpp"
#include "wordlist.hpp"


// TODO: - Que faire si le joueur n'a pas les cartes pour placer son mot ?
//       - Les coups doivent être saisis sur une seule ligne de texte
//       - Les cartes des joueurs éliminés sont distribués aux joueurs restants
//       - Lorsqu’il n’y a plus de carte dans le talon, la pile des cartes exposées est reprise, battue et remise sur la table dans la position originale
//       - Réarranger le contenu des fichiers
//       - Vérifier la dé-allocation de la mémoire dynamique
//       - Documentation du code
//       - Préconditions
//       - Nombre de joueurs en arguments de ligne de commande
//       - Renommage des structures, fonctions, et variables
//       - Tests unitaires
//       - Placer la boucle principale dans gamelogic.cpp
//       - IsEmpty function for containers
//
//


// TODO: Move in gameinterface.cpp
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


int main(int argc, const char* argv[])
{
    const unsigned int playerCount = ReadPlayerCount(argc, argv);

    if (!playerCount)
        return EXIT_FAILURE;

    PlayerList players = PlayerListCreate(playerCount);
    CardList gameCards = CreateGameCards();

    DistributeCards(players, gameCards);

    // TODO: Prendre l'ownership plutôt que de copier
    CardStack talonCards = CardStackFromCardList(gameCards);
    CardStack exposedCards = CardStackCreate();

    CardStackPush(exposedCards, CardStackPop(talonCards));

    DisplayValidCommands();

    WordList placedWords = WordListCreate();
    WordList dictionary = ReadDictionary();

    if (ListSize(dictionary) != DICTIONARY_WORD_COUNT)
    {
        std::cerr << "Erreur lors de la lecture du dictionnaire de mots" << std::endl;
        return EXIT_FAILURE;
    }

    while (true)
    {
        DisplayGameState(players, exposedCards, placedWords);

        Command cmd {};

        if (!ReadPlayerCommand(cmd))
        {
            DisplayInvalidCommand();
            continue;
        }

        Player& currentPlayer = GetCurrentPlayer(players);

        switch (cmd.name)
        {
            case Commands::TALON:
                CommandTalon(cmd, currentPlayer, exposedCards, talonCards);
                break;

            case Commands::EXPOSED:
                CommandExposed(cmd, currentPlayer, exposedCards);
                break;

            case Commands::PLACE:
                CommandPlace(cmd, currentPlayer, placedWords, dictionary);
                break;

            case Commands::REPLACE:
                CommandReplace(cmd, currentPlayer, placedWords, dictionary);
                break;

            case Commands::COMPLETE:
                CommandComplete(cmd, currentPlayer, placedWords, dictionary);
                break;

            default:
                DisplayInvalidCommand();
                continue;
        }

        if (HasPlayerWonRound(currentPlayer))
        {
            DisplayScores(players);
            UpdateLosers(players);

            if (IsGameOver(players))
            {
                DisplayGameOver();
                break;
            }
        }

        RotateCurrentPlayer(players);
    }

    WordListDestroy(dictionary);
    WordListDestroy(placedWords);
    PlayerListDestroy(players);
    CardListDestroy(gameCards);
    CardStackDestroy(talonCards);
    CardStackDestroy(exposedCards);

    return EXIT_SUCCESS;
}
