#include "Tests.hpp"
#include "TestWordList.hpp"
#include "AutoDestructors.hpp"



void TEST_WordList_Size()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        WordListAuto wl;
        TEST_CASE_ASSERT(ListSize(wl) == 0);
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        WordListAuto wl(10);
        TEST_CASE_ASSERT(ListSize(wl) == 0);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_At()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("At");

        WordListAuto wl;

        CardList a = CardListCopyString("valeur1");
        CardList b = CardListCopyString("valeur2");

        WordListAppend(wl, a);
        WordListAppend(wl, b);

        TEST_CASE_ASSERT(CardListCompare(WordAt(wl, 0), WordAt(wl, 1)) == -1);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_SetAt()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("SetAt");

        WordListAuto wl;

        CardList a = CardListCopyString("valeur1");
        CardList b = CardListCopyString("valeur2");
        CardList c = CardListCopy(b);

        WordListAppend(wl, a);

        SetWordAt(wl, 0, b);

        TEST_CASE_ASSERT(CardListCompare(WordAt(wl, 0), c) == 0);

        CardListDestroy(c);
    }

    TEST_FUNCTION_ENTER();
}

void TEST_WordList_Append()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        WordListAuto wl;

        for (size_t i = 0; i < 10; ++i)
        {
            CardList cl = CardListCreate();
            WordListAppend(wl, cl);
        }

        TEST_CASE_ASSERT(ListSize(wl) == 10);
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        WordListAuto wl(5);

        for (size_t i = 0; i < 10; ++i)
        {
            CardList cl = CardListCreate();
            WordListAppend(wl, cl);
        }

        TEST_CASE_ASSERT(ListSize(wl) == 10);
        TEST_CASE_ASSERT(wl.words.capacity >= 10);
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
