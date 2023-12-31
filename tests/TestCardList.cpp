#include "Tests.hpp"
#include "TestCardList.hpp"
#include "AutoDestructors.hpp"

void TEST_CardList_Clear()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Liste deja vide");

        CardListAuto cl;

        CardListClear(cl);
        TEST_CASE_ASSERT(IsEmpty(cl));
    }

    {
        TEST_CASE_ENTER("Liste non vide");

        CardListAuto cl(5);
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');

        CardListClear(cl);
        TEST_CASE_ASSERT(IsEmpty(cl));
        TEST_CASE_ASSERT(cl.cards.capacity == 5);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Compare()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Collections vides");

        CardListAuto cl1;
        CardListAuto cl2;

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 0);
    }

    {
        TEST_CASE_ENTER("Collection gauche vide");

        CardListAuto cl1;
        CardListAuto cl2;
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == -1);
    }

    {
        TEST_CASE_ENTER("Collection de droite vide");

        CardListAuto cl1;
        CardListAuto cl2;
        CardListAppend(cl1, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    {
        TEST_CASE_ENTER("Non vides et egales");

        CardListAuto cl1(CardListCopyString("IUT"));
        CardListAuto cl2(CardListCopyString("IUT"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 0);
    }

    {
        TEST_CASE_ENTER("Non vides et non-egales");

        CardListAuto cl1(CardListCopyString("IUT"));
        CardListAuto cl2(CardListCopyString("BUT"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) != 0);
    }

    {
        TEST_CASE_ENTER("Collection de meme taille et gauche superieure");

        CardListAuto cl1(CardListCopyString("AAB"));
        CardListAuto cl2(CardListCopyString("AAA"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    {
        TEST_CASE_ENTER("Collections de meme taille et droite superieure");

        CardListAuto cl1(CardListCopyString("AAA"));
        CardListAuto cl2(CardListCopyString("AAB"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == -1);
    }

    {
        TEST_CASE_ENTER("Collection de tailles differentes et gauche superieure");

        CardListAuto cl1(CardListCopyString("AAAA"));
        CardListAuto cl2(CardListCopyString("AAA"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    {
        TEST_CASE_ENTER("Collections de tailles differentes et droite superieure");

        CardListAuto cl1(CardListCopyString("AAA"));
        CardListAuto cl2(CardListCopyString("AAAA"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == -1);
    }

    {
        TEST_CASE_ENTER("Contenu plus long mais inferieur");

        CardListAuto cl1(CardListCopyString("BBB"));
        CardListAuto cl2(CardListCopyString("AAAA"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardListCopyString()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Chaine vide");

        CardListAuto cl1(CardListCopyString(nullptr));

        TEST_CASE_ASSERT(IsEmpty(cl1));
        TEST_CASE_ASSERT(ListSize(cl1) == 0);
    }

    {
        TEST_CASE_ENTER("Chaine non vide");

        CardListAuto cl1(CardListCopyString("AZOTE"));

        TEST_CASE_ASSERT_FALSE(IsEmpty(cl1));
        TEST_CASE_ASSERT(CardAt(cl1, 0) == 'A');
        TEST_CASE_ASSERT(CardAt(cl1, 1) == 'Z');
        TEST_CASE_ASSERT(CardAt(cl1, 2) == 'O');
        TEST_CASE_ASSERT(CardAt(cl1, 3) == 'T');
        TEST_CASE_ASSERT(CardAt(cl1, 4) == 'E');
        TEST_CASE_ASSERT(ListSize(cl1) == 5);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Empty()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite a 0");
        CardListAuto cl;
        TEST_CASE_ASSERT(IsEmpty(cl));
    }

    {
        TEST_CASE_ENTER("Capacite positive");
        CardListAuto cl(10);
        TEST_CASE_ASSERT(IsEmpty(cl));
    }

    {
        TEST_CASE_ENTER("Ajout d'une carte");
        CardListAuto cl;
        CardListAppend(cl, 'A');
        TEST_CASE_ASSERT_FALSE(IsEmpty(cl));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Size()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite a 0");
        CardListAuto cl;
        TEST_CASE_ASSERT(ListSize(cl) == 0);
    }

    {
        TEST_CASE_ENTER("Capacite positive");
        CardListAuto cl;
        TEST_CASE_ASSERT(ListSize(cl) == 0);
    }

    {
        TEST_CASE_ENTER("Ajout d'une carte");
        CardListAuto cl;
        CardListAppend(cl, 'A');
        TEST_CASE_ASSERT(ListSize(cl) == 1);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Copy()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Collection vide");

        CardListAuto copied;
        CardListAuto copy(CardListCopy(copied));

        TEST_CASE_ASSERT(IsEmpty(copied));
        TEST_CASE_ASSERT(IsEmpty(copy));
    }

    {
        TEST_CASE_ENTER("Collection non-vide");

        CardListAuto copied(CardListCopyString("ABCDEFGHIJ"));
        CardListAuto copy(CardListCopy(copied));

        TEST_CASE_ASSERT_FALSE(IsEmpty(copied));
        TEST_CASE_ASSERT_FALSE(IsEmpty(copy));
        TEST_CASE_ASSERT(ListSize(copied) == 10);
        TEST_CASE_ASSERT(ListSize(copy) == 10);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_IndexOf()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Liste vide");

        CardListAuto cl;
        size_t index;

        TEST_CASE_ASSERT_FALSE(CardListIndexOf(cl, 'J', index));
    }

    {
        TEST_CASE_ENTER("Element existant");

        CardListAuto cl(CardListCopyString("AKJLT"));
        size_t index;

        TEST_CASE_ASSERT(CardListIndexOf(cl, 'J', index));
        TEST_CASE_ASSERT(index == 2);
    }

    {
        TEST_CASE_ENTER("Element inexistant");
        CardListAuto cl(CardListCopyString("AKBLT"));
        size_t index;

        TEST_CASE_ASSERT_FALSE(CardListIndexOf(cl, 'J', index));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_At()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("CardAt");

        const char* str = "DEHLDZEFKGAZ";
        CardList tmp = CardListCopyString(str);
        CardListAuto cl(tmp);

        for (size_t i = 0; i < ListSize(cl); ++i)
        {
            TEST_CASE_ASSERT(CardAt(cl, i) == str[i]);
        }
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Append()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Ajout quand la capacite est nulle");

        CardListAuto cl;

        TEST_CASE_ASSERT(cl.cards.capacity == 0);

        CardListAppend(cl, 'R');

        TEST_CASE_ASSERT(CardAt(cl, 0));
        TEST_CASE_ASSERT(cl.cards.capacity > 0);
        TEST_CASE_ASSERT_FALSE(IsEmpty(cl));
    }

    {
        TEST_CASE_ENTER("Reallocation");

        CardListAuto cl(5);

        for (size_t i = 0; i < 5; ++i)
            CardListAppend(cl, 'L');

        TEST_CASE_ASSERT(ListSize(cl) == cl.cards.capacity);

        CardListAppend(cl, 'L');

        TEST_CASE_ASSERT(ListSize(cl) > 5);
        TEST_CASE_ASSERT(cl.cards.capacity >= ListSize(cl));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Remove()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Collection vide");

        CardListAuto cl;

        size_t size_before_removal = ListSize(cl);
        CardListRemove(cl, 'A');
        size_t size_after_removal = ListSize(cl);

        TEST_CASE_ASSERT(size_after_removal == size_before_removal);
    }

    {
        TEST_CASE_ENTER("Collection non vide element non existant");

        CardListAuto cl(CardListCopyString("MALISTEDECARTE"));

        size_t size_before_removal = ListSize(cl);
        CardListRemove(cl, 'J');
        size_t size_after_removal = ListSize(cl);

        TEST_CASE_ASSERT(size_after_removal == size_before_removal);
    }

    {
        TEST_CASE_ENTER("Collection non vide element existant une fois");

        CardListAuto cl1(CardListCopyString("MALISTEDECARTE"));

        size_t size_before_removal = ListSize(cl1);
        CardListRemove(cl1, 'C');
        size_t size_after_removal = ListSize(cl1);

        TEST_CASE_ASSERT(size_after_removal == size_before_removal - 1);

        CardListAuto cl2(CardListCopyString("MALISTEDEARTE"));

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 0);
    }

    {
        TEST_CASE_ENTER("Collection non vide element existant plusieurs fois");

        CardListAuto cl(CardListCopyString("MALISTEDECARTE"));

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT(ListSize(cl) == 13);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT(ListSize(cl) == 12);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT(ListSize(cl) == 11);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT(ListSize(cl) == 11);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_RemoveAt()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Simple");

        CardListAuto cl(CardListCopyString("ABCDEF"));

        CardListRemoveAt(cl, 0);
        TEST_CASE_ASSERT(CardAt(cl, 0) == 'B');

        size_t previous_size = ListSize(cl);
        while (!IsEmpty(cl))
        {
            CardListRemoveAt(cl, ListSize(cl) - 1);

            TEST_CASE_ASSERT(ListSize(cl) == previous_size - 1);

            previous_size = ListSize(cl);
        }
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_RemoveLast()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Suppression depuis l'arrière");
        CardListAuto cl(CardListCopyString("TESTBUFFER"));

        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'R');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'E');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'F');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'F');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'U');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'B');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'T');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'S');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'E');
        TEST_CASE_ASSERT(CardListRemoveLast(cl) == 'T');
        TEST_CASE_ASSERT(IsEmpty(cl));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Difference()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Listes vides");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAuto diff(CardListDifference(cl1, cl2));

        TEST_CASE_ASSERT(IsEmpty(diff));
    }

    {
        TEST_CASE_ENTER("Listes egales");

        CardListAuto cl1(CardListCopyString("DIFFERENCES"));
        CardListAuto cl2(CardListCopyString("DIFFERENCES"));
        CardListAuto cl3(CardListDifference(cl1, cl2));

        TEST_CASE_ASSERT(IsEmpty(cl3));
    }

    {
        TEST_CASE_ENTER("Listes differentes meme tailles");

        CardListAuto cl1(CardListCopyString("DITFERENSES"));
        CardListAuto cl2(CardListCopyString("DIFFRRYNCES"));

        CardListAuto diff1(CardListDifference(cl1, cl2));
        CardListAuto diff2(CardListDifference(cl2, cl1));

        TEST_CASE_ASSERT(ListSize(diff1) == 4);
        TEST_CASE_ASSERT(ListSize(diff2) == 4);

        size_t unused;

        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'T', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'E', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'E', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'S', unused));

        TEST_CASE_ASSERT(CardListIndexOf(diff2, 'F', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff2, 'R', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff2, 'Y', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff2, 'C', unused));
    }

    {
        TEST_CASE_ENTER("Listes differentes tailles differentes");

        CardListAuto cl1(CardListCopyString("DROITES"));
        CardListAuto cl2(CardListCopyString("DOS"));

        CardListAuto diff1(CardListDifference(cl1, cl2));
        CardListAuto diff2(CardListDifference(cl2, cl1));

        TEST_CASE_ASSERT(ListSize(diff1) == 4);
        TEST_CASE_ASSERT(IsEmpty(diff2));

        size_t unused;

        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'R', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'I', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'T', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'E', unused));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_COMPONENT_CardList()
{
    TEST_COMPONENT_ENTER();

    TEST_CardList_Clear();
    TEST_CardList_Empty();
    TEST_CardList_Copy();
    TEST_CardList_Size();
    TEST_CardList_IndexOf();
    TEST_CardList_At();
    TEST_CardList_Append();
    TEST_CardList_Remove();
    TEST_CardList_RemoveAt();
    TEST_CardList_RemoveLast();
    TEST_CardList_Compare();
    TEST_CardList_Difference();
    TEST_CardListCopyString();

    TEST_COMPONENT_LEAVE();
}