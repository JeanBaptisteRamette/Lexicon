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

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'I');
        CardListAppend(cl1, 'U');
        CardListAppend(cl1, 'T');

        CardListAppend(cl2, 'I');
        CardListAppend(cl2, 'U');
        CardListAppend(cl2, 'T');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 0);
    }

    {
        TEST_CASE_ENTER("Non vides et non-egales");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'I');
        CardListAppend(cl1, 'U');
        CardListAppend(cl1, 'T');

        CardListAppend(cl2, 'B');
        CardListAppend(cl2, 'U');
        CardListAppend(cl2, 'T');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) != 0);
    }

    {
        TEST_CASE_ENTER("Collection de meme taille et gauche superieure");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'B');

        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    {
        TEST_CASE_ENTER("Collections de meme taille et droite superieure");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');

        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'B');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == -1);
    }

    {
        TEST_CASE_ENTER("Collection de tailles differentes et gauche superieure");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');

        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    {
        TEST_CASE_ENTER("Collections de tailles differentes et droite superieure");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');
        CardListAppend(cl1, 'A');

        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == -1);
    }

    {
        TEST_CASE_ENTER("Contenu plus long mais inferieur");

        CardListAuto cl1;
        CardListAuto cl2;

        CardListAppend(cl1, 'B');
        CardListAppend(cl1, 'B');
        CardListAppend(cl1, 'B');

        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 1);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_FromBuffer()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Buffer vide");

        CardList other1 = CardListCopyString(nullptr);
        CardListAuto cl1(other1);

        TEST_CASE_ASSERT(IsEmpty(cl1));
        TEST_CASE_ASSERT(ListSize(cl1) == 0);
    }

    {
        TEST_CASE_ENTER("Buffer non vide");

        CardList other1 = CardListCopyString("AZOTE");
        CardListAuto cl1(other1);

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

        CardList tmp = CardListCopy(copied);
        CardListAuto copy(tmp);

        TEST_CASE_ASSERT(IsEmpty(copied));
        TEST_CASE_ASSERT(IsEmpty(copy));
    }

    {
        TEST_CASE_ENTER("Collection non-vide");

        CardList tmp = CardListCopyString("ABCDEFGHIJ");
        CardListAuto copied(tmp);

        tmp = CardListCopy(copied);
        CardListAuto copy(tmp);

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

        CardList tmp = CardListCopyString("AKJLT");
        CardListAuto cl(tmp);
        size_t index;

        TEST_CASE_ASSERT(CardListIndexOf(cl, 'J', index));
        TEST_CASE_ASSERT(index == 2);
    }

    {
        TEST_CASE_ENTER("Element inexistant");
        CardList tmp = CardListCopyString("AKBLT");
        CardListAuto cl(tmp);
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

        CardList tmp = CardListCopyString("MALISTEDECARTE");
        CardListAuto cl(tmp);

        size_t size_before_removal = ListSize(cl);
        CardListRemove(cl, 'J');
        size_t size_after_removal = ListSize(cl);

        TEST_CASE_ASSERT(size_after_removal == size_before_removal);
    }

    {
        TEST_CASE_ENTER("Collection non vide element existant une fois");

        CardList tmp1 = CardListCopyString("MALISTEDECARTE");
        CardListAuto cl1(tmp1);

        size_t size_before_removal = ListSize(cl1);
        CardListRemove(cl1, 'C');
        size_t size_after_removal = ListSize(cl1);

        TEST_CASE_ASSERT(size_after_removal == size_before_removal - 1);

        CardList tmp2 = CardListCopyString("MALISTEDEARTE");
        CardListAuto cl2(tmp2);

        TEST_CASE_ASSERT(CardListCompare(cl1, cl2) == 0);
    }

    {
        TEST_CASE_ENTER("Collection non vide element existant plusieurs fois");

        CardList tmp1 = CardListCopyString("MALISTEDECARTE");
        CardListAuto cl(tmp1);

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

        CardListAuto cl;
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'B');
        CardListAppend(cl, 'C');
        CardListAppend(cl, 'D');
        CardListAppend(cl, 'E');
        CardListAppend(cl, 'F');

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
        CardList tmp = CardListCopyString("TESTBUFFER");
        CardListAuto cl(tmp);

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

        CardList tmp = CardListDifference(cl1, cl2);
        CardListAuto diff(tmp);

        TEST_CASE_ASSERT(IsEmpty(diff));
    }

    {
        TEST_CASE_ENTER("Listes egales");

        CardList tmp1 = CardListCopyString("DIFFERENCES");
        CardList tmp2 = CardListCopyString("DIFFERENCES");
        CardList diff = CardListDifference(tmp1, tmp2);

        CardListAuto cl1(tmp1);
        CardListAuto cl2(tmp2);
        CardListAuto cl3(diff);

        TEST_CASE_ASSERT(IsEmpty(cl3));
    }

    {
        TEST_CASE_ENTER("Listes differentes meme tailles");

        CardList tmp1 = CardListCopyString("DITFERENSES");
        CardList tmp2 = CardListCopyString("DIFFRRYNCES");
        CardList diff1 = CardListDifference(tmp1, tmp2);
        CardList diff2 = CardListDifference(tmp2, tmp1);

        CardListAuto cl1(tmp1);
        CardListAuto cl2(tmp2);

        CardListAuto cl3(diff1);
        CardListAuto cl4(diff2);

        TEST_CASE_ASSERT(ListSize(cl3) == 4);
        TEST_CASE_ASSERT(ListSize(cl4) == 4);

        size_t unused;

        TEST_CASE_ASSERT(CardListIndexOf(cl3, 'T', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl3, 'E', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl3, 'E', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl3, 'S', unused));

        TEST_CASE_ASSERT(CardListIndexOf(cl4, 'F', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl4, 'R', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl4, 'Y', unused));
        TEST_CASE_ASSERT(CardListIndexOf(cl4, 'C', unused));
    }

    {
        TEST_CASE_ENTER("Listes differentes tailles differentes");

        CardList tmp1 = CardListCopyString("DROITES");
        CardList tmp2 = CardListCopyString("DOS");

        CardList diff1 = CardListDifference(tmp1, tmp2);
        CardList diff2 = CardListDifference(tmp2, tmp1);

        TEST_CASE_ASSERT(ListSize(diff1) == 4);
        TEST_CASE_ASSERT(IsEmpty(diff2));

        size_t unused;

        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'R', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'I', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'T', unused));
        TEST_CASE_ASSERT(CardListIndexOf(diff1, 'E', unused));

        CardListDestroy(tmp1);
        CardListDestroy(tmp2);
        CardListDestroy(diff1);
        CardListDestroy(diff2);
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
    TEST_CardList_FromBuffer();

    TEST_COMPONENT_LEAVE();
}