/*!
 * @file Logic.cpp
 * @brief Implémente la logique du jeu: commandes, boucle principale, gestion des cartes, vérification dictionnaire
 */


#include <cassert>
#include <cstdlib>
#include <ctime>
#include "Logic.hpp"
#include "Definitions.hpp"
#include "Interface.hpp"
#include "GameData.hpp"
#include "Players.hpp"


bool ExecuteCommand(const Command& cmd, GameData& game)
{
    Player& currentPlayer = GetCurrentPlayer(game.players);

    // Trouve la commande correspondante à la lettre entrée par l'utilisateur et l'exécute
    switch (cmd.name)
    {
        case Commands::TALON:
            return CommandTalon(cmd, currentPlayer, game.exposedCards, game.talonCards);

        case Commands::EXPOSED:
            return CommandExposed(cmd, currentPlayer, game.exposedCards);

        case Commands::PLACE:
            return CommandPlace(cmd, currentPlayer, game.placedWords, game.dictionary);

        case Commands::REPLACE:
            return CommandReplace(cmd, currentPlayer, game.placedWords, game.dictionary);

        case Commands::COMPLETE:
            return CommandComplete(cmd, currentPlayer, game.placedWords, game.dictionary);

        default:
            return false;
    }
}

void GameRun(GameData& game)
{
    DisplayValidCommands();

    // Boucle principale du jeu, on en sort quand il n'y a plus qu'un joueur
    while (EnoughPlayers(game.players))
    {
        DisplayGameState(game);

        Command cmd {};

        // Lire, valider et exécuter la commande entrée par le joueur
        // Le joueur doit rejouer si la commande est invalide
        if (!ReadPlayerCommand(cmd) || !ExecuteCommand(cmd, game))
        {
            DisplayInvalidCommand();
            continue;
        }

        // Vérifier si le joueur actuel a posé toutes ses cartes, et donc a gagné le tour
        if (HasPlayerWonRound(GetCurrentPlayer(game.players)))
        {
            UpdateScores(game.players);
            DisplayScores(game.players);
            UpdateLosers(game.players);
            RedistributeCards(game);
            SetRoundStarter(game.players);
        }
        else
        {
            // Passer au joueur suivant
            RotateCurrentPlayer(game.players);
        }

        // Recycler la pile des cartes exposées pour remplir le talon s'il est vide
        if (IsEmpty(game.talonCards))
            ReuseExposedCards(game.talonCards, game.exposedCards);
    }

    DisplayGameOver();
}

void ReuseExposedCards(CardStack& talonCards, CardStack& exposedCards)
{
    assert(!IsEmpty(exposedCards));

    ShuffleCards(exposedCards.list);

    // Placer toutes les cartes, sauf une, de la pile des cartes exposées sur le talon
    while (ListSize(exposedCards.list) != 1)
        CardStackPush(talonCards, CardStackPop(exposedCards));
}

CardStack CreateGameCards()
{
    // Allouer le paquet de carte
    CardStack gameCards = CardStackCreate(CARDS_COUNT_GAME);

    // Tableau associant chaque lettre à son nombre de cartes dans le jeu. Voir annexe
    unsigned int quantities[CARDS_COUNT_VALUES] = {
            2, 2, 2, 2, 5, 1, 2, 2, 4,
            1, 1, 2, 1, 3, 2, 1, 1, 3,
            3, 3, 3, 1, 1, 1, 1, 1
    };

    // Pour chaque lettre, ajouter quantities[indice lettre] cartes
    for (Card cardIndex = 0; cardIndex < CARDS_COUNT_VALUES; ++cardIndex)
        while (quantities[cardIndex]--)
            CardStackPush(gameCards, CARD_VALUE(cardIndex));

    return gameCards;
}

void ShuffleCards(CardList& cards)
{
    if (IsEmpty(cards))
        return;

    srand(time(nullptr));

    for (size_t i = ListSize(cards) - 1; i > 0; --i)
    {
        const size_t j = rand() % (i + 1);

        const Card c = CardAt(cards, i);

        // Echange des cartes aux indices i et j
        SetCardAt(cards, i, CardAt(cards, j));
        SetCardAt(cards, j, c);
    }
}

void DistributeCards(PlayerList& players, CardStack& cards)
{
    // Mélanger les cartes avant de les distribuer
    ShuffleCards(cards.list);

    for (size_t i = 0; i < ListSize(players); ++i)
    {
        Player& player = PlayerAt(players, i);

        // Distribuer seulement si le joueur est actif
        if (!player.lost)
        {
            for (size_t j = 0; j < CARDS_COUNT_PLAYER; ++j)
                CardListAppend(player.cards, CardStackPop(cards));
        }
    }
}

void RedistributeCards(GameData& game)
{
    // Enlever les cartes de la main de chaque joueur
    for (size_t i = 0; i < ListSize(game.players); ++i)
    {
        Player& player = PlayerAt(game.players, i);
        CardListClear(player.cards);
    }

    // Détruire, réinitialiser et replacer les cartes dans l'état initial
    GameCardsDestroy(game);
    GameCardsInit(game);
    GameCardsSetup(game);
}

bool CommandTalon(const Command& params, Player& player, CardStack& exposedCards, CardStack& talonCards)
{
    const Card card = params.card;

    size_t index;

    // S'assurer que le joueur possède la carte qu'il veut échanger
    if (!CardListIndexOf(player.cards, card, index))
        return false;

    // Supprimer la carte de la main du joueur
    CardListRemoveAt(player.cards, index);

    // La carte correspondante est placée au-dessus des cartes exposées
    CardStackPush(exposedCards, card);

    // La première carte du talon est ramassée par le joueur.
    const Card popped = CardStackPop(talonCards);
    CardListAppend(player.cards, popped);

    return true;
}

bool CommandExposed(const Command& params, Player& player, CardStack& exposedCards)
{
    const Card card = params.card;

    size_t index;

    // S'assurer que le joueur possède la carte qu'il veut échanger
    if (!CardListIndexOf(player.cards, card, index))
        return false;

    // Remplacer par la carte en haut de la pile
    SetCardAt(player.cards, index, CardStackPop(exposedCards));

    // Placer la carte remplacée en haut de la pile
    CardStackPush(exposedCards, card);

    return true;
}

bool HasCards(const Player& player, const CardList& cards)
{
    // Tableau comptant le nombre d'occurrences de chaque lettre dans une collection de cartes
    int occurrences[CARDS_COUNT_VALUES] = { 0 };

    // Compter le nombre d'occurrences pour les cartes du joueur
    for (size_t i = 0; i < ListSize(player.cards); ++i)
    {
        const Card letter = CardAt(player.cards, i);
        ++occurrences[CARD_NO(letter)];
    }

    // Compter le nombre d'occurrences pour la liste de carte
    for (size_t i = 0; i < ListSize(cards); ++i)
    {
        const Card letter = CardAt(cards, i);

        // Vérifier si le joueur possède assez de fois la carte
        if (--occurrences[CARD_NO(letter)] < 0)
            return false;
    }

    return true;
}

bool IsWordValid(const WordList& dictionary, const CardList& word)
{
    // Le dictionnaire étant trié dans l'ordre lexicographique, on peut utiliser une recherche dichotomique
    // On utilise un type signé pour les limites afin d'éviter un dépassement d'entier lorsque middle = 0

    int lowerBound = 0;
    int upperBound = static_cast<int>(ListSize(dictionary) - 1);

    while (lowerBound <= upperBound)
    {
        const int middle = lowerBound + (upperBound - lowerBound) / 2;
        const int ret = CardListCompare(word, WordAt(dictionary, middle));

        if (ret == 0)
            return true;
        else if (ret == 1)
            lowerBound = middle + 1;
        else
            upperBound = middle - 1;
    }

    return false;
}

bool CommandPlace(const Command& params, Player& player, WordList& placedWords, const WordList& dictionary)
{
    CardList word = params.cards;

    // 1. Vérifier que le joueur peut placer le mot
    if (!HasCards(player, word))
    {
        CardListDestroy(word);
        return false;
    }

    // 2. Vérifier que le mot est valide selon le dictionnaire
    if (!IsWordValid(dictionary, word))
    {
        ApplyScorePenalty(player);
        DisplayInvalidWord();
        CardListDestroy(word);
        return true;
    }

    // 3. Supprimer les cartes utilisées de la main du joueur
    for (size_t i = 0; i < ListSize(word); ++i)
        CardListRemove(player.cards, CardAt(word, i));

    // 4. Ajouter le mot à la liste de mot placés sur la table
    WordListAppend(placedWords, word);

    return true;
}

bool CommandReplace(const Command& params, Player& player, WordList& placedWords, const WordList& dictionary)
{
    const size_t wordIndex = params.wordIndex;
    CardList newWord = params.cards;

    // Vérifier que l'indice du mot est valide
    if (wordIndex >= ListSize(placedWords))
    {
        CardListDestroy(newWord);
        return false;
    }

    CardList& oldWord = WordAt(placedWords, wordIndex);

    // Le nouveau mot doit avoir la même taille que celui remplacé
    if (ListSize(oldWord) != ListSize(newWord))
    {
        CardListDestroy(newWord);
        return false;
    }

    CardList replacedCards = CardListCreate(ListSize(oldWord));
    CardList replacerCards = CardListCreate(ListSize(newWord));

    // Récupérer toutes les cartes remplaçantes et toutes les cartes remplacées dans deux listes
    for (size_t i = 0; i < ListSize(oldWord); ++i)
    {
        const Card a = CardAt(oldWord, i);
        const Card b = CardAt(newWord, i);

        if (a != b)
        {
            CardListAppend(replacedCards, a);
            CardListAppend(replacerCards, b);
        }
    }

    // Vérifier que le joueur possède les cartes remplaçantes
    if (!HasCards(player, replacerCards))
    {
        CardListDestroy(newWord);
        CardListDestroy(replacedCards);
        CardListDestroy(replacerCards);
        return false;
    }

    // Vérifier que le nouveau mot est valide
    if (!IsWordValid(dictionary, newWord))
    {
        ApplyScorePenalty(player);
        DisplayInvalidWord();

        CardListDestroy(newWord);
        CardListDestroy(replacedCards);
        CardListDestroy(replacerCards);
        return true;
    }

    // Remplacer le mot complété
    SetWordAt(placedWords, wordIndex, newWord);

    // Supprimer les cartes utilisées pour remplacer et récupérer les cartes remplacées
    for (size_t i = 0; i < ListSize(replacerCards); ++i)
    {
        CardListRemove(player.cards, CardAt(replacerCards, i));
        CardListAppend(player.cards, CardAt(replacedCards, i));
    }

    CardListDestroy(replacedCards);
    CardListDestroy(replacerCards);

    return true;
}

bool IncludesOrdered(const CardList& a, const CardList& b)
{
    assert(!IsEmpty(b));

    size_t j = 0;

    // Algorithme linéaire sur b
    for (size_t i = 0; i < ListSize(a); ++i)
    {
        while (CardAt(b, j) != CardAt(a, i))
        {
            // Augmenter le curseur de b tant qu'on a pas trouvé le caractère de a
            ++j;

            // Si on a déjà atteint la fin de la liste, alors b ne peut pas inclure a
            if (j >= ListSize(b))
                return false;
        }
    }

    return true;
}

bool CommandComplete(const Command& params, Player& player, WordList& placedWords, const WordList& dictionary)
{
    const size_t wordIndex = params.wordIndex;
    CardList newWord = params.cards;

    // Vérifier que l'indice du mot est valide
    if (wordIndex >= ListSize(placedWords))
    {
        CardListDestroy(newWord);
        return false;
    }

    CardList& oldWord = WordAt(placedWords, wordIndex);

    if (ListSize(newWord) <= ListSize(oldWord))
    {
        CardListDestroy(newWord);
        return false;
    }

    // Vérifier que le mot à compléter est une sous-séquence ordonnée du nouveau mot
    if (!IncludesOrdered(oldWord, newWord))
    {
        CardListDestroy(newWord);
        return false;
    }

    // Trouve les cartes utilisées par le joueur
    CardList usedCards = CardListDifference(newWord, oldWord);

    // Vérifier que le joueur possède les cartes utilisées pour former le mot
    if (!HasCards(player, usedCards))
    {
        CardListDestroy(newWord);
        CardListDestroy(usedCards);
        return false;
    }

    if (IsWordValid(dictionary, newWord))
    {
        // Ajouter le mot s'il est valide
        SetWordAt(placedWords, wordIndex, newWord);

        // Supprimer les cartes utilisées par le joueur
        for (size_t i = 0; i < ListSize(usedCards); ++i)
            CardListRemove(player.cards, CardAt(usedCards, i));
    }
    else
    {
        // Mot invalide, malus + message
        ApplyScorePenalty(player);
        DisplayInvalidWord();
        CardListDestroy(newWord);
    }

    CardListDestroy(usedCards);
    return true;
}
