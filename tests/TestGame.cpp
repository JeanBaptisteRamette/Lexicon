#include "Tests.hpp"
#include "TestGame.hpp"
#include "../src/Game/Logic.hpp"
#include "AutoDestructors.hpp"


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

void TEST_Game_UpdateScores()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Cartes");

        PlayerListAuto players(2);
        Player& player = PlayerAt(players, 0);

        for (size_t i = 0; i < 10; ++i)
            CardListAppend(player.cards, 'A');

        UpdateScores(players);

        TEST_CASE_ASSERT_FALSE(player.lost);

        CardListAppend(player.cards, 'Z');
        UpdateScores(players);

        TEST_CASE_ASSERT(player.lost);
    }

    {
        TEST_CASE_ENTER("Penalites");

        PlayerListAuto players(2);
        Player& player = PlayerAt(players, 0);

        for (size_t i = 0; i < 99 / INVALID_WORD_PENALTY; ++i)
            ApplyScorePenalty(player);

        UpdateScores(players);
        TEST_CASE_ASSERT_FALSE(player.lost);

        ApplyScorePenalty(player);

        UpdateScores(players);
        TEST_CASE_ASSERT(player.lost);
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

void TEST_COMPONENT_Game()
{
    TEST_COMPONENT_ENTER();

    TEST_Game_ReuseExposedCards();
    TEST_Game_CreateGameCards();
    TEST_Game_DistributeCards();
    TEST_Game_ShuffleCards();
    TEST_Game_UpdateScores();
    TEST_Game_HasCards();
    TEST_Game_IsWordValid();
    TEST_Game_IncludesOrdered();

    TEST_COMPONENT_LEAVE();
}
