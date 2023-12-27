#include <iostream>
#include "gameinterface.hpp"
#include "gamelogic.hpp"
#include "gamedata.hpp"


// TODO: - Les cartes des joueurs éliminés sont distribués aux joueurs restants
//       - Lorsqu’il n’y a plus de carte dans le talon, la pile des cartes exposées est reprise, battue et remise sur la table dans la position originale
//       - Réarranger le contenu des fichiers
//       - Vérifier la dé-allocation de la mémoire dynamique
//       - Préconditions
//       - Renommage des structures, fonctions, et variables
//       - Tests unitaires
//
//

int main(int argc, const char* argv[])
{
    const unsigned int playerCount = ReadPlayerCount(argc, argv);

    if (!playerCount)
        return EXIT_FAILURE;

    GameData gameData {};

    int ec = EXIT_FAILURE;

    if (InitGameData(gameData, playerCount))
    {
        GameRun(gameData);
        ec = EXIT_SUCCESS;
    }

    DestroyGameData(gameData);
    return ec;
}
