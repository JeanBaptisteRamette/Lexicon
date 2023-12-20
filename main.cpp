#include <iostream>
#include "gameinterface.hpp"
#include "definitions.hpp"
#include "gamelogic.hpp"
#include "players.hpp"
#include "cardstack.hpp"
#include "cardlist.hpp"
#include "wordlist.hpp"


// #include <algorithm>


// TODO: Que faire si le joueur n'a pas les cartes pour placer son mot ?

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Nombre de players manquant\n";
        return EXIT_FAILURE;
    }

    /*
     * TODO: Make players' cards sorted for faster algorithm
     * const auto v1 = {'a', 'b', 'c', 'f', 'h', 'x'};
     * const auto v2 = {'a', 'b', 'c'};
     * const auto v3 = {'a', 'c'};

     * std::cout << std::boolalpha << std::ranges::includes(v1, v2) << std::endl;
     * std::cout << std::boolalpha << std::ranges::includes(v1, v3) << std::endl;
     */

    PlayerList players = PlayerListCreate(4);
    CardList gameCards = CreateGameCards();

    DistributeCards(players, gameCards);

    // TODO: Prendre l'ownership plutôt que de copier
    CardStack talonCards = CardStackFromCardList(gameCards);
    CardStack exposedCards = CardStackCreate(1);

    CardStackPush(exposedCards, CardStackPop(talonCards));

    DisplayValidCommands();

    WordList placedWords = WordListCreate(0);
    WordList dictionary = ReadDictionary();

    if (ListSize(dictionary) == 0)
    {
        std::cerr << "Erreur lors de la lecture du dictionnaire de mots" << std::endl;
        return EXIT_FAILURE;
    }

    while (true)
    {
        DisplayGameState(players, exposedCards, placedWords);

        const Command command = GetPlayerCommand();

        Player& currentPlayer = GetCurrentPlayer(players);

        switch (command) {
            case TALON:
                CommandTalon(currentPlayer, exposedCards, talonCards);
                break;

            case EXPOSED:
                CommandExposed(currentPlayer, exposedCards);
                break;

            case PLACE:
                CommandPlace(currentPlayer, placedWords, dictionary);
                break;

            case REPLACE:
                CommandReplace(currentPlayer, placedWords, dictionary);
                break;

            case COMPLETE:
                CommandComplete(currentPlayer, placedWords, dictionary);
                break;

            default:
                DisplayInvalidCommand();
                break;
        }

        NextPlayer(players);
    }

    WordListDestroy(dictionary);
    PlayerListDestroy(players);
    CardListDestroy(gameCards);
    CardStackDestroy(talonCards);
    CardStackDestroy(exposedCards);
    WordListDestroy(placedWords);

    return EXIT_SUCCESS;
}
