#include <sstream>
#include "Tests.hpp"
#include "TestGame.hpp"
#include "../src/Game/Logic.hpp"
#include "AutoDestructors.hpp"


void TEST_Game_ReadCommandFromStream()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Commandes valides: T");

        Command cmd {};
        std::istringstream stream("T E");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'T');
        TEST_CASE_ASSERT(cmd.card == 'E');
    }

    {
        TEST_CASE_ENTER("Commandes valides: E");

        Command cmd {};
        std::istringstream stream("E B");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'E');
        TEST_CASE_ASSERT(cmd.card == 'B');
    }

    {
        TEST_CASE_ENTER("Commandes valides: P");

        Command cmd {};
        std::istringstream stream("P FOIN");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'P');
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "FOIN", 4) == 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides: R");

        Command cmd {};
        std::istringstream stream("R 23 DEAARKFJAHFRKC");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'R');
        TEST_CASE_ASSERT(cmd.wordIndex == 22);
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "DEAARKFJAHFRKC", 14) == 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides: C");

        Command cmd {};
        std::istringstream stream("C 100 MAISOOOOOOON");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'C');
        TEST_CASE_ASSERT(cmd.wordIndex == 99);
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "MAISOOOOOOON", 12) == 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: T");

        Command cmd {};
        std::istringstream stream("     T      E        ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'T');
        TEST_CASE_ASSERT(cmd.card == 'E');
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: E");

        Command cmd {};
        std::istringstream stream("   E              B ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'E');
        TEST_CASE_ASSERT(cmd.card == 'B');
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: P");

        Command cmd {};
        std::istringstream stream("   P     FOIN ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'P');
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "FOIN", 4) == 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: R");

        Command cmd {};
        std::istringstream stream("   R    23       DEAARKFJAHFRKC     ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'R');
        TEST_CASE_ASSERT(cmd.wordIndex == 22);
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "DEAARKFJAHFRKC", 14) == 0);

        CardListDestroy(cmd.cards);
    }

    {
        TEST_CASE_ENTER("Commandes valides espaces multiples: C");

        Command cmd {};
        std::istringstream stream("  C     100   MAISOOOOOOON   ");
        ReadCommandFromStream(cmd, stream);

        TEST_CASE_ASSERT(cmd.name == 'C');
        TEST_CASE_ASSERT(cmd.wordIndex == 99);
        TEST_CASE_ASSERT(std::strncmp(cmd.cards.cards, "MAISOOOOOOON", 12) == 0);

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
            TEST_CASE_ASSERT(CARD_NO(ptr[i]) == i);
            TEST_CASE_ASSERT(CARD_VALUE(i) == ptr[i]);
        }
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_ShuffleCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Liste vide");

        CardListAuto cl;
        ShuffleCards(cl);

        TEST_CASE_ASSERT(IsEmpty(cl));
    }

    {
        TEST_CASE_ENTER("Un seul element");

        CardListAuto cl(1);
        CardListAppend(cl, 'A');

        ShuffleCards(cl);

        TEST_CASE_ASSERT(ListSize(cl) == 1);
        TEST_CASE_ASSERT(CardAt(cl, 0) == 'A');
    }

    {
        TEST_CASE_ENTER("Plusieurs elements");

        CardList tmp1 = CardListCopyString("ABCDEFGHIJKLMNOP");
        CardList tmp2 = CardListCopy(tmp1);

        CardListAuto cl1(tmp1);
        CardListAuto cl2(tmp2);

        ShuffleCards(cl1);

        TEST_CASE_ASSERT(ListSize(cl2) == ListSize(cl2));

        for (size_t i = 0; i < ListSize(cl2); ++i)
        {
            Card c = CardAt(cl2, i);
            size_t unused;
            TEST_CASE_ASSERT(CardListIndexOf(cl1, c, unused));
        }
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_ReuseExposedCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Reuse");

        CardList tmp = CardListCopyString("AABBCCDDEE");

        CardStack ec {};
        CardStackAssignList(ec, tmp);

        CardStackAuto exposedCards(ec);
        CardStackAuto talonCards;

        ReuseExposedCards(talonCards, exposedCards);

        TEST_CASE_ASSERT(ListSize(exposedCards.cards.list) == 1);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_CreateGameCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Create");

        CardStack cs = CreateGameCards();
        CardStackAuto gameCards(cs);

        TEST_CASE_ASSERT(ListSize(gameCards.cards.list) == CARDS_COUNT_GAME);
        TEST_CASE_ASSERT(gameCards.cards.list.capacity == CARDS_COUNT_GAME);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_DistributeCards()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Distribution");

        PlayerListAuto players(4);

        CardStack cs = CreateGameCards();
        CardStackAuto talon(cs);

        DistributeCards(players, talon);

        TEST_CASE_ASSERT(ListSize(talon.cards.list) == CARDS_COUNT_GAME - ListSize(players) * CARDS_COUNT_PLAYER);
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

        TEST_CASE_ASSERT(player.score == 100);

        CardListAppend(player.cards, 'Z');
        UpdatePlayerScore(player);

        TEST_CASE_ASSERT(player.score == 100 + 102);
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

        TEST_CASE_ASSERT(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    {
        TEST_CASE_ENTER("Cartes espacees et pas dans le meme ordre");

        Player player {};
        player.cards = CardListCopyString("MAPITSAONG");

        CardList word = CardListCopyString("SONMAI");

        TEST_CASE_ASSERT(HasCards(player, word));

        CardListDestroy(word);
        CardListDestroy(player.cards);
    }

    {
        TEST_CASE_ENTER("Lettre plusieurs fois présente");

        Player player {};
        player.cards = CardListCopyString("APOKRILISURETSE");

        CardList word = CardListCopyString("RAPETISSER");

        TEST_CASE_ASSERT(HasCards(player, word));

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

        WordListAuto dictionary;
        WordListAppend(dictionary, CardListCopyString("ARBRE"));
        WordListAppend(dictionary, CardListCopyString("MAISON"));
        WordListAppend(dictionary, CardListCopyString("PAIN"));
        WordListAppend(dictionary, CardListCopyString("ZEBRE"));

        CardList tmp = CardListCopyString("MAISON");
        CardListAuto word(tmp);

        TEST_CASE_ASSERT(IsWordValid(dictionary, word));
    }

    {
        TEST_CASE_ENTER("Mot Invalide");

        WordListAuto dictionary;
        WordListAppend(dictionary, CardListCopyString("ARBRE"));
        WordListAppend(dictionary, CardListCopyString("MAISON"));
        WordListAppend(dictionary, CardListCopyString("PAIN"));
        WordListAppend(dictionary, CardListCopyString("ZEBRE"));

        CardList tmp = CardListCopyString("ARBRES");
        CardListAuto word(tmp);

        TEST_CASE_ASSERT_FALSE(IsWordValid(dictionary, word));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_IncludesOrdered()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Ordonnee");

        CardList tmp1 = CardListCopyString("DOS");
        CardList tmp2 = CardListCopyString("DROITES");

        CardListAuto cl1(tmp1);
        CardListAuto cl2(tmp2);

        TEST_CASE_ASSERT(IncludesOrdered(cl1, cl2));

        CardList tmp3 = CardListCopyString("MER");
        CardList tmp4 = CardListCopyString("AMERTUMES");

        CardListAuto cl3(tmp3);
        CardListAuto cl4(tmp4);

        TEST_CASE_ASSERT(IncludesOrdered(cl3, cl4));

        CardList tmp5 = CardListCopyString("PQRST");
        CardList tmp6 = CardListCopyString("AAAAAPQRST");

        CardListAuto cl5(tmp5);
        CardListAuto cl6(tmp6);

        TEST_CASE_ASSERT(IncludesOrdered(cl5, cl6));

        CardList tmp7 = CardListCopyString("PQRST");
        CardList tmp8 = CardListCopyString("APAPQARRRASSSAT");

        CardListAuto cl7(tmp7);
        CardListAuto cl8(tmp8);

        TEST_CASE_ASSERT(IncludesOrdered(cl7, cl8));
    }

    {
        TEST_CASE_ENTER("Non-ordonnee");

        CardList tmp1 = CardListCopyString("DSO");
        CardList tmp2 = CardListCopyString("DROITES");

        CardListAuto cl1(tmp1);
        CardListAuto cl2(tmp2);

        TEST_CASE_ASSERT_FALSE(IncludesOrdered(cl1, cl2));

        CardList tmp3 = CardListCopyString("EMR");
        CardList tmp4 = CardListCopyString("AMERTUMES");

        CardListAuto cl3(tmp3);
        CardListAuto cl4(tmp4);

        TEST_CASE_ASSERT_FALSE(IncludesOrdered(cl3, cl4));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_Game_UpdateLosers()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Tout score >= 100 croissants");

        PlayerListAuto pl(MAX_PLAYER_COUNT);
        Player* players = pl.players.players;
        players[0].score = 100;
        players[1].score = 101;
        players[2].score = 102;
        players[3].score = 103;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_FALSE(players[0].lost);
        TEST_CASE_ASSERT(players[1].lost);
        TEST_CASE_ASSERT(players[2].lost);
        TEST_CASE_ASSERT(players[3].lost);
    }

    {
        TEST_CASE_ENTER("Tout score >= 100 decroissants");

        PlayerListAuto pl(MAX_PLAYER_COUNT);
        Player* players = pl.players.players;

        players[0].score = 103;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 100;

        UpdateLosers(pl);

        TEST_CASE_ASSERT(players[0].lost);
        TEST_CASE_ASSERT(players[1].lost);
        TEST_CASE_ASSERT(players[2].lost);
        TEST_CASE_ASSERT_FALSE(players[3].lost);
    }

    {
        TEST_CASE_ENTER("premier score < 100");

        PlayerListAuto pl(MAX_PLAYER_COUNT);
        Player* players = pl.players.players;

        players[0].score = 70;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 103;

        UpdateLosers(pl);

        TEST_CASE_ASSERT_FALSE(players[0].lost);
        TEST_CASE_ASSERT(players[1].lost);
        TEST_CASE_ASSERT(players[2].lost);
        TEST_CASE_ASSERT(players[3].lost);
    }

    {
        TEST_CASE_ENTER("dernier score < 100");

        PlayerListAuto pl(MAX_PLAYER_COUNT);
        Player* players = pl.players.players;

        players[0].score = 103;
        players[1].score = 102;
        players[2].score = 101;
        players[3].score = 70;

        UpdateLosers(pl);

        TEST_CASE_ASSERT(players[0].lost);
        TEST_CASE_ASSERT(players[1].lost);
        TEST_CASE_ASSERT(players[2].lost);
        TEST_CASE_ASSERT_FALSE(players[3].lost);
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
