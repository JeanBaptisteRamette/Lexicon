#include "Tests.hpp"
#include "TestWordList.hpp"
#include "../src/Game/Containers/WordList.hpp"



void TEST_WordList_Size()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        WordList wl = WordListCreate();
        TEST_CASE_ASSERT_EQUAL(ListSize(wl), 0);
        WordListDestroy(wl);
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        WordList wl = WordListCreate(10);
        TEST_CASE_ASSERT_EQUAL(ListSize(wl), 0);
        WordListDestroy(wl);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_At()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("At");

        WordList wl = WordListCreate(2);

        CardList a = CardListCopyString("valeur1");
        CardList b = CardListCopyString("valeur2");

        WordListAppend(wl, a);
        WordListAppend(wl, b);

        TEST_CASE_ASSERT_EQUAL(CardListCompare(WordAt(wl, 0), WordAt(wl, 1)), -1);

        WordListDestroy(wl);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_SetAt()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("SetAt");

        WordList wl = WordListCreate();

        CardList a = CardListCopyString("valeur1");
        CardList b = CardListCopyString("valeur2");
        CardList c = CardListCopy(b);

        WordListAppend(wl, a);

        SetWordAt(wl, 0, b);

        TEST_CASE_ASSERT_EQUAL(CardListCompare(WordAt(wl, 0), c), 0);

        CardListDestroy(c);
        WordListDestroy(wl);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_Append()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        WordList wl = WordListCreate(10);

        for (size_t i = 0; i < 10; ++i)
        {
            CardList cl = CardListCreate();
            WordListAppend(wl, cl);
        }

        TEST_CASE_ASSERT_EQUAL(ListSize(wl), 10);
        WordListDestroy(wl);
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        WordList wl = WordListCreate(5);

        for (size_t i = 0; i < 10; ++i)
        {
            CardList cl = CardListCreate();
            WordListAppend(wl, cl);
        }

        TEST_CASE_ASSERT_EQUAL(ListSize(wl), 10);
        TEST_CASE_ASSERT_TRUE(wl.capacity >= 10);

        WordListDestroy(wl);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_COMPONENT_WordList()
{
    TEST_COMPONENT_ENTER();

    TEST_WordList_Size();
    TEST_WordList_At();
    TEST_WordList_SetAt();
    TEST_WordList_Append();

    TEST_COMPONENT_LEAVE();
}
