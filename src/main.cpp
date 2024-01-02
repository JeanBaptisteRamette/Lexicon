/*!
 * @file main.cpp
 * @brief Point d'entrée du programme
 */


#include <cstdlib>

#include "Game/Interface.hpp"
#include "Game/GameData.hpp"
#include "Game/Logic.hpp"


/*!
 * Point d'entrée du programme
 */
int main(int argc, const char* argv[])
{
    //
    // 1. Lire le nombre de joueurs depuis les arguments du programme
    //
    const unsigned int playerCount = ReadPlayerCount(argc, argv);

    if (!playerCount)
        return EXIT_FAILURE;

    GameData gameData {};

    int ec = EXIT_FAILURE;


    //
    // 2. Initialiser les données du jeu (joueurs, cartes, dictionnaire)
    //
    if (InitGameData(gameData, playerCount))
    {
        //
        // 3. Lancer le jeu
        //
        GameRun(gameData);
        ec = EXIT_SUCCESS;
    }

    //
    // 4. Désallouer les données du jeu
    //
    DestroyGameData(gameData);

    return ec;
}
