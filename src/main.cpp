#include <iostream>

#include "Game/Interface.hpp"
#include "Game/Logic.hpp"
#include "Game/GameData.hpp"



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
