#include <sstream>
#include "TestGame.hpp"
#include "Tests.hpp"
#include "../src/Game/Logic.hpp"


void TEST_Game_ReadCommandFromStream()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Commandes valides: T");

        Command cmd {};
        std::istringstream stream("T E");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'T');
        TEST_CASE_ASSERT_EQUAL(cmd.card, 'E');
    }

    {
        TEST_CASE_ENTER("Commandes valides: E");

        Command cmd {};
        std::istringstream stream("E B");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'E');
        TEST_CASE_ASSERT_EQUAL(cmd.card, 'B');
    }

    {
        TEST_CASE_ENTER("Commandes valides: P");

        Command cmd {};
        std::istringstream stream("P FOIN");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'P');
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "FOIN", 4), 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides: R");

        Command cmd {};
        std::istringstream stream("R 23 DEAARKFJAHFRKC");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'R');
        TEST_CASE_ASSERT_EQUAL(cmd.wordIndex, 22);
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "DEAARKFJAHFRKC", 14), 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides: C");

        Command cmd {};
        std::istringstream stream("C 100 MAISOOOOOOON");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'C');
        TEST_CASE_ASSERT_EQUAL(cmd.wordIndex, 99);
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "MAISOOOOOOON", 12), 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: T");

        Command cmd {};
        std::istringstream stream("     T      E        ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'T');
        TEST_CASE_ASSERT_EQUAL(cmd.card, 'E');
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: E");

        Command cmd {};
        std::istringstream stream("   E              B ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'E');
        TEST_CASE_ASSERT_EQUAL(cmd.card, 'B');
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: P");

        Command cmd {};
        std::istringstream stream("   P     FOIN ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'P');
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "FOIN", 4), 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: R");

        Command cmd {};
        std::istringstream stream("   R    23       DEAARKFJAHFRKC     ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'R');
        TEST_CASE_ASSERT_EQUAL(cmd.wordIndex, 22);
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "DEAARKFJAHFRKC", 14), 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: C");

        Command cmd {};
        std::istringstream stream("  C     100   MAISOOOOOOON   ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT_EQUAL(cmd.name, 'C');
        TEST_CASE_ASSERT_EQUAL(cmd.wordIndex, 99);
        TEST_CASE_ASSERT_EQUAL(std::strncmp(cmd.cards.cards, "MAISOOOOOOON", 12), 0);

        CardListDestroy(cmd.cards);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_CardConversions()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("CARD_NO et CARD_VALUE");

        const char* ptr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        for (unsigned int i = 0; i < strlen(ptr); ++i)
        {
            TEST_CASE_ASSERT_EQUAL(CARD_NO(ptr[i]), i);
            TEST_CASE_ASSERT_EQUAL(CARD_VALUE(i), ptr[i]);
        }
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_ShuffleCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Liste vide");

        CardList cl = CardListCreate();
        ShuffleCards(cl);

        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));
        CardListDestroy(cl);
    }

    {
        TEST_CASE_ENTER("Un seul element");

        CardList cl = CardListCreate(1);
        CardListAppend(cl, 'A');

        ShuffleCards(cl);

        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 1);
        TEST_CASE_ASSERT_EQUAL(CardAt(cl, 0), 'A');

        CardListDestroy(cl);
    }

    {
        TEST_CASE_ENTER("Plusieurs elements");

        CardList cl1 = CardListCopyString("ABCDEFGHIJKLMNOP");
        CardList cl2 = CardListCopy(cl1);

        ShuffleCards(cl1);

        TEST_CASE_ASSERT_EQUAL(ListSize(cl1), ListSize(cl2));

        for (size_t i = 0; i < ListSize(cl2); ++i)
        {
            Card c = CardAt(cl2, i);
            size_t unused;
            TEST_CASE_ASSERT_TRUE(CardListIndexOf(cl1, c, unused));
        }

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_ReuseExposedCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Reuse");

        CardList tmp = CardListCopyString("AABBCCDDEE");

        CardStack exposedCards { .list = tmp };
        CardStack talonCards = CardStackCreate();

        ReuseExposedCards(talonCards, exposedCards);

        TEST_CASE_ASSERT_EQUAL(ListSize(exposedCards.list), 1);

        CardStackDestroy(exposedCards);
        CardStackDestroy(talonCards);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_CreateGameCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Create");

        CardStack gameCards = CreateGameCards();

        TEST_CASE_ASSERT_EQUAL(ListSize(gameCards.list), CARDS_COUNT_GAME);
        TEST_CASE_ASSERT_EQUAL(gameCards.list.capacity, CARDS_COUNT_GAME);

        CardStackDestroy(gameCards);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_DistributeCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Distribution");

        PlayerList players = PlayerListCreate(4);

        CardStack talon = CreateGameCards();

        DistributeCards(players, talon);

        TEST_CASE_ASSERT_EQUAL(ListSize(talon.list), CARDS_COUNT_GAME - ListSize(players) * CARDS_COUNT_PLAYER);

        PlayerListDestroy(players);
        CardStackDestroy(talon);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_UpdatePlayerScore()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Cartes");

        Player player {};

        for (size_t i = 0; i < 10; ++i)
            CardListAppend(player.cards, 'A');

        UpdatePlayerScore(player);

        TEST_CASE_ASSERT_EQUAL(player.score, 100);

        CardListAppend(player.cards, 'Z');
        UpdatePlayerScore(player);

        TEST_CASE_ASSERT_EQUAL(player.score, 100 + 102);

        CardListDestroy(player.cards);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_HasCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Carte dans l'ordre");

        Player player {};
        player.cards = CardListCopyString("MAISONPART");

        CardList word = CardListCopyString("MAISON");

        TEST_CASE_ASSERT_TRUE(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    {
        TEST_CASE_ENTER("Cartes espacees et pas dans le meme ordre");

        Player player {};
        player.cards = CardListCopyString("MAPITSAONG");

        CardList word = CardListCopyString("SONMAI");

        TEST_CASE_ASSERT_TRUE(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    {
        TEST_CASE_ENTER("Lettre plusieurs fois présente");

        Player player {};
        player.cards = CardListCopyString("APOKRILISURETSE");

        CardList word = CardListCopyString("RAPETISSER");

        TEST_CASE_ASSERT_TRUE(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    {
        TEST_CASE_ENTER("Faux");

        Player player {};
        player.cards = CardListCopyString("APOKRILIURETSE");

        CardList word = CardListCopyString("RAPETISSER");

        TEST_CASE_ASSERT_FALSE(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_IsWordValid()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Mot Valide");

        WordList dictionary = WordListCreate();
        WordListAppend(dictionary, CardListCopyString("ARBRE"));
        WordListAppend(dictionary, CardListCopyString("MAISON"));
        WordListAppend(dictionary, CardListCopyString("PAIN"));
        WordListAppend(dictionary, CardListCopyString("ZEBRE"));

        CardList word = CardListCopyString("MAISON");

        TEST_CASE_ASSERT_TRUE(IsWordValid(dictionary, word));

        WordListDestroy(dictionary);
        CardListDestroy(word);
    }

    {
        TEST_CASE_ENTER("Mot Invalide");

        WordList dictionary = WordListCreate();
        WordListAppend(dictionary, CardListCopyString("ARBRE"));
        WordListAppend(dictionary, CardListCopyString("MAISON"));
        WordListAppend(dictionary, CardListCopyString("PAIN"));
        WordListAppend(dictionary, CardListCopyString("ZEBRE"));

        CardList word = CardListCopyString("ARBRES");

        TEST_CASE_ASSERT_FALSE(IsWordValid(dictionary, word));

        WordListDestroy(dictionary);
        CardListDestroy(word);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_IncludesOrdered()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Ordonnee");

        CardList cl1 = CardListCopyString("DOS");
        CardList cl2 = CardListCopyString("DROITES");
        TEST_CASE_ASSERT_TRUE(IncludesOrdered(cl1, cl2));

        CardList cl3 = CardListCopyString("MER");
        CardList cl4 = CardListCopyString("AMERTUMES");
        TEST_CASE_ASSERT_TRUE(IncludesOrdered(cl3, cl4));

        CardList cl5 = CardListCopyString("PQRST");
        CardList cl6 = CardListCopyString("AAAAAPQRST");
        TEST_CASE_ASSERT_TRUE(IncludesOrdered(cl5, cl6));

        CardList cl7 = CardListCopyString("PQRST");
        CardList cl8 = CardListCopyString("APAPQARRRASSSAT");
        TEST_CASE_ASSERT_TRUE(IncludesOrdered(cl7, cl8));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
        CardListDestroy(cl3);
        CardListDestroy(cl4);
        CardListDestroy(cl5);
        CardListDestroy(cl6);
        CardListDestroy(cl7);
        CardListDestroy(cl8);
    }

    {
        TEST_CASE_ENTER("Non-ordonnee");

        CardList cl1 = CardListCopyString("DSO");
        CardList cl2 = CardListCopyString("DROITES");
        TEST_CASE_ASSERT_FALSE(IncludesOrdered(cl1, cl2));

        CardList cl3 = CardListCopyString("EMR");
        CardList cl4 = CardListCopyString("AMERTUMES");
        TEST_CASE_ASSERT_FALSE(IncludesOrdered(cl3, cl4));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
        CardListDestroy(cl3);
        CardListDestroy(cl4);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_UpdateLosers()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Tout score >= 100 croissants");

        PlayerList pl = PlayerListCreate(MAX_PLAYER_COUNT);
        Player* players = pl.players;
        players[0].score = 100;
        players[1].score = 101;
        players[2].score = 102;
        players[3].score = 103;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_FALSE(players[0].lost);
        TEST_CASE_ASSERT_TRUE(players[1].lost);
        TEST_CASE_ASSERT_TRUE(players[2].lost);
        TEST_CASE_ASSERT_TRUE(players[3].lost);

        PlayerListDestroy(pl);
    }

    {
        TEST_CASE_ENTER("Tout score >= 100 decroissants");

        PlayerList pl = PlayerListCreate(MAX_PLAYER_COUNT);
        Player* players = pl.players;

        players[0].score = 103;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 100;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_TRUE(players[0].lost);
        TEST_CASE_ASSERT_TRUE(players[1].lost);
        TEST_CASE_ASSERT_TRUE(players[2].lost);
        TEST_CASE_ASSERT_FALSE(players[3].lost);

        PlayerListDestroy(pl);
    }

    {
        TEST_CASE_ENTER("premier score < 100");

        PlayerList pl = PlayerListCreate(MAX_PLAYER_COUNT);
        Player* players = pl.players;

        players[0].score = 70;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 103;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_FALSE(players[0].lost);
        TEST_CASE_ASSERT_TRUE(players[1].lost);
        TEST_CASE_ASSERT_TRUE(players[2].lost);
        TEST_CASE_ASSERT_TRUE(players[3].lost);

        PlayerListDestroy(pl);
    }

    {
        TEST_CASE_ENTER("dernier score < 100");

        PlayerList pl = PlayerListCreate(MAX_PLAYER_COUNT);
        Player* players = pl.players;

        players[0].score = 103;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 70;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_TRUE(players[0].lost);
        TEST_CASE_ASSERT_TRUE(players[1].lost);
        TEST_CASE_ASSERT_TRUE(players[2].lost);
        TEST_CASE_ASSERT_FALSE(players[3].lost);

        PlayerListDestroy(pl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_COMPONENT_Game()
{
    TEST_COMPONENT_ENTER();

    TEST_Game_ReadCommandFromStream();
    TEST_Game_CardConversions();
    TEST_Game_UpdateLosers();
    TEST_Game_ReuseExposedCards();
    TEST_Game_CreateGameCards();
    TEST_Game_DistributeCards();
    TEST_Game_ShuffleCards();
    TEST_Game_UpdatePlayerScore();
    TEST_Game_HasCards();
    TEST_Game_IsWordValid();
    TEST_Game_IncludesOrdered();


    TEST_COMPONENT_LEAVE();
}
