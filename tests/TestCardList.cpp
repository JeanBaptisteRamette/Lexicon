/*!
 * @file TestCardList
 * @brief Définitions et implémentation des tests du composant CardList
 */

#include "TestCardList.hpp"
#include "Tests.hpp"
#include "../src/Game/Containers/CardList.hpp"


void TEST_CardList_Clear()
{
    TEST_FUNCTION_ENTER();

    TEST_CASE_DEFINE("Liste déja vide")
	{
        CardList cl = CardListCreate();

        CardListClear(cl);
        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));

        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Liste non vide")
    {
        CardList cl = CardListCreate(5);
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');
        CardListAppend(cl, 'A');

        CardListClear(cl);
        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));
        TEST_CASE_ASSERT_EQUAL(cl.capacity, 5);

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Compare()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Collections vides")
    {
        CardList cl1 = CardListCreate();
        CardList cl2 = CardListCreate();

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 0);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collection gauche vide")
    {

        CardList cl1 = CardListCreate();
        CardList cl2 = CardListCreate();
        CardListAppend(cl2, 'A');

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), -1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collection de droite vide")
    {

        CardList cl1 = CardListCreate();
        CardList cl2 = CardListCreate();
        CardListAppend(cl1, 'A');

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Non vides et egales")
    {
        CardList cl1 = CardListCopyString("IUT");
        CardList cl2 = CardListCopyString("IUT");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 0);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Non vides et non-egales")
    {
        CardList cl1 = CardListCopyString("IUT");
        CardList cl2 = CardListCopyString("BUT");

        TEST_CASE_ASSERT_UNEQUAL(CardListCompare(cl1, cl2), 0);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collection de meme taille et gauche superieure")
    {

        CardList cl1 = CardListCopyString("AAB");
        CardList cl2 = CardListCopyString("AAA");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collections de meme taille et droite superieure")
    {
        CardList cl1 = CardListCopyString("AAA");
        CardList cl2 = CardListCopyString("AAB");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), -1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collection de tailles differentes et gauche superieure")
    {

        CardList cl1 = CardListCopyString("AAAA");
        CardList cl2 = CardListCopyString("AAA");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collections de tailles differentes et droite superieure")
    {
        CardList cl1 = CardListCopyString("AAA");
        CardList cl2 = CardListCopyString("AAAA");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), -1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Contenu plus long mais inferieur")
    {
        CardList cl1 = CardListCopyString("BBB");
        CardList cl2 = CardListCopyString("AAAA");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 1);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardListCopyString()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Chaine vide")
    {
        CardList cl1 = CardListCopyString(nullptr);

        TEST_CASE_ASSERT_TRUE(IsEmpty(cl1));
        TEST_CASE_ASSERT_EQUAL(ListSize(cl1), 0);

        CardListDestroy(cl1);
    }

	TEST_CASE_DEFINE("Chaine non vide")
    {
        CardList cl1 = CardListCopyString("AZOTE");

        TEST_CASE_ASSERT_FALSE(IsEmpty(cl1));
        TEST_CASE_ASSERT_EQUAL(CardAt(cl1, 0), 'A');
        TEST_CASE_ASSERT_EQUAL(CardAt(cl1, 1), 'Z');
        TEST_CASE_ASSERT_EQUAL(CardAt(cl1, 2), 'O');
        TEST_CASE_ASSERT_EQUAL(CardAt(cl1, 3), 'T');
        TEST_CASE_ASSERT_EQUAL(CardAt(cl1, 4), 'E');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl1), 5);

        CardListDestroy(cl1);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Empty()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Capacite a 0")
    {
        CardList cl = CardListCreate();
        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Capacite positive")
    {
        CardList cl = CardListCreate(10);
        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Ajout d'une carte")
    {
        CardList cl = CardListCreate();
        CardListAppend(cl, 'A');
        TEST_CASE_ASSERT_FALSE(IsEmpty(cl));
        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Size()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Capacite a 0")
    {
        CardList cl = CardListCreate();
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 0);
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Capacite positive")
    {
        CardList cl = CardListCreate(10);
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 0);
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Ajout d'une carte")
    {
        CardList cl = CardListCreate();
        CardListAppend(cl, 'A');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 1);
        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Copy()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Collection vide")
    {
        CardList copied = CardListCreate();
        CardList copy = CardListCopy(copied);

        TEST_CASE_ASSERT_TRUE(IsEmpty(copied));
        TEST_CASE_ASSERT_TRUE(IsEmpty(copy));

        CardListDestroy(copied);
        CardListDestroy(copy);
    }

	TEST_CASE_DEFINE("Collection non-vide")
    {
        CardList copied = CardListCopyString("ABCDEFGHIJ");
        CardList copy = CardListCopy(copied);

        TEST_CASE_ASSERT_FALSE(IsEmpty(copied));
        TEST_CASE_ASSERT_FALSE(IsEmpty(copy));
        TEST_CASE_ASSERT_EQUAL(ListSize(copied), 10);
        TEST_CASE_ASSERT_EQUAL(ListSize(copy), 10);

        CardListDestroy(copied);
        CardListDestroy(copy);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_IndexOf()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Liste vide")
    {
        CardList cl = CardListCreate();
        size_t index;

        TEST_CASE_ASSERT_FALSE(CardListIndexOf(cl, 'J', index));
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Element existant")
    {
        CardList cl = CardListCopyString("AKJLT");
        size_t index;

        TEST_CASE_ASSERT_TRUE(CardListIndexOf(cl, 'J', index));
        TEST_CASE_ASSERT_EQUAL(index, 2);

        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Element inexistant")
    {
        CardList cl = CardListCopyString("AKBLT");
        size_t index;

        TEST_CASE_ASSERT_FALSE(CardListIndexOf(cl, 'J', index));

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_At()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("CardAt")
    {
        const char* str = "DEHLDZEFKGAZ";
        CardList cl = CardListCopyString(str);

        for (size_t i = 0; i < ListSize(cl); ++i)
        {
            TEST_CASE_ASSERT_EQUAL(CardAt(cl, i),  str[i]);
        }

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Append()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Ajout quand la capacite est nulle")
    {
        CardList cl = CardListCreate();

        TEST_CASE_ASSERT_EQUAL(cl.capacity, 0);

        CardListAppend(cl, 'R');

        TEST_CASE_ASSERT_TRUE(CardAt(cl, 0));
        TEST_CASE_ASSERT_TRUE(cl.capacity > 0);
        TEST_CASE_ASSERT_FALSE(IsEmpty(cl));

        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Reallocation")
    {
        CardList cl = CardListCreate(5);

        for (size_t i = 0; i < 5; ++i)
            CardListAppend(cl, 'L');

        TEST_CASE_ASSERT_EQUAL(ListSize(cl), cl.capacity);

        CardListAppend(cl, 'L');

        TEST_CASE_ASSERT_TRUE(ListSize(cl) > 5);
        TEST_CASE_ASSERT_TRUE(cl.capacity >= ListSize(cl));

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Remove()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Collection vide")
    {
        CardList cl = CardListCreate();

        size_t size_before_removal = ListSize(cl);
        CardListRemove(cl, 'A');
        size_t size_after_removal = ListSize(cl);

        TEST_CASE_ASSERT_EQUAL(size_after_removal, size_before_removal);
        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Collection non vide element non existant")
    {
        CardList cl(CardListCopyString("MALISTEDECARTE"));

        size_t size_before_removal = ListSize(cl);
        CardListRemove(cl, 'J');
        size_t size_after_removal = ListSize(cl);

        TEST_CASE_ASSERT_EQUAL(size_after_removal, size_before_removal);

        CardListDestroy(cl);
    }

	TEST_CASE_DEFINE("Collection non vide element existant une fois")
    {
        CardList cl1 = CardListCopyString("MALISTEDECARTE");

        size_t size_before_removal = ListSize(cl1);
        CardListRemove(cl1, 'C');
        size_t size_after_removal = ListSize(cl1);

        TEST_CASE_ASSERT_EQUAL(size_after_removal, size_before_removal - 1);

        CardList cl2 = CardListCopyString("MALISTEDEARTE");

        TEST_CASE_ASSERT_EQUAL(CardListCompare(cl1, cl2), 0);

        CardListDestroy(cl1);
        CardListDestroy(cl2);
    }

	TEST_CASE_DEFINE("Collection non vide element existant plusieurs fois")
    {
        CardList cl = CardListCopyString("MALISTEDECARTE");

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 13);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 12);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 11);

        CardListRemove(cl, 'E');
        TEST_CASE_ASSERT_EQUAL(ListSize(cl), 11);

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_RemoveAt()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Simple")
    {
        CardList cl = CardListCopyString("ABCDEF");

        CardListRemoveAt(cl, 0);
        TEST_CASE_ASSERT_EQUAL(CardAt(cl, 0), 'B');

        size_t previous_size = ListSize(cl);
        while (!IsEmpty(cl))
        {
            CardListRemoveAt(cl, ListSize(cl) - 1);

            TEST_CASE_ASSERT_EQUAL(ListSize(cl), previous_size - 1);

            previous_size = ListSize(cl);
        }

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_RemoveLast()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Suppression depuis l'arrière")
    {
        CardList cl = CardListCopyString("TESTBUFFER");

        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'R');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'E');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'F');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'F');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'U');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'B');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'T');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'S');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'E');
        TEST_CASE_ASSERT_EQUAL(CardListRemoveLast(cl), 'T');
        TEST_CASE_ASSERT_TRUE(IsEmpty(cl));

        CardListDestroy(cl);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardList_Difference()
{
    TEST_FUNCTION_ENTER();

	TEST_CASE_DEFINE("Listes vides")
    {
        CardList cl1 = CardListCreate();
        CardList cl2 = CardListCreate();

        CardList diff = CardListDifference(cl1, cl2);

        TEST_CASE_ASSERT_TRUE(IsEmpty(diff));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
        CardListDestroy(diff);
    }

	TEST_CASE_DEFINE("Listes egales")
    {
        CardList cl1 = CardListCopyString("DIFFERENCES");
        CardList cl2 = CardListCopyString("DIFFERENCES");
        CardList cl3 = CardListDifference(cl1, cl2);

        TEST_CASE_ASSERT_TRUE(IsEmpty(cl3));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
        CardListDestroy(cl3);
    }

	TEST_CASE_DEFINE("Listes differentes meme tailles")
    {
        CardList cl1 = CardListCopyString("DITFERENSES");
        CardList cl2 = CardListCopyString("DIFFRRYNCES");

        CardList diff1 = CardListDifference(cl1, cl2);
        CardList diff2 = CardListDifference(cl2, cl1);

        TEST_CASE_ASSERT_EQUAL(ListSize(diff1), 4);
        TEST_CASE_ASSERT_EQUAL(ListSize(diff2), 4);

        size_t unused;

        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'T', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'E', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'E', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'S', unused));

        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff2, 'F', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff2, 'R', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff2, 'Y', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff2, 'C', unused));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
        CardListDestroy(diff1);
        CardListDestroy(diff2);
    }

	TEST_CASE_DEFINE("Listes differentes tailles differentes")
    {
        CardList cl1 = CardListCopyString("DROITES");
        CardList cl2 = CardListCopyString("DOS");

        CardList diff1 = CardListDifference(cl1, cl2);
        CardList diff2 = CardListDifference(cl2, cl1);

        TEST_CASE_ASSERT_EQUAL(ListSize(diff1), 4);
        TEST_CASE_ASSERT_TRUE(IsEmpty(diff2));

        size_t unused;

        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'R', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'I', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'T', unused));
        TEST_CASE_ASSERT_TRUE(CardListIndexOf(diff1, 'E', unused));

        CardListDestroy(cl1);
        CardListDestroy(cl2);
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
    TEST_CardListCopyString();

    TEST_COMPONENT_LEAVE();
}