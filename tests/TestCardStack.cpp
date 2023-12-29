#include "TestCardStack.hpp"
#include "Tests.hpp"
#include "../cardstack.hpp"


struct CardStackAuto
{
    CardStack cards;

    CardStackAuto(size_t cap = 0) : cards(CardStackCreate(cap)) {}

    ~CardStackAuto()
    {
        CardStackDestroy(cards);
    }

    operator CardStack&()
    {
        return cards;
    }
};


void TEST_CardStack_AssignList()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Liste vide");

        CardList list = CardListCreate();
        CardStackAuto stack;

        CardStackAssignList(stack, list);

        TEST_CASE_ASSERT(IsEmpty(stack));
    }

    {
        TEST_CASE_ENTER("Liste non vide");

        CardList list = CardListCreate();
        CardListAppend(list, 'A');
        CardListAppend(list, 'B');
        CardListAppend(list, 'C');

        CardStackAuto stack;

        CardStackAssignList(stack, list);

        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        TEST_CASE_ASSERT(CardAt(stack.cards.list, 0) == 'A');
        TEST_CASE_ASSERT(CardAt(stack.cards.list, 1) == 'B');
        TEST_CASE_ASSERT(CardAt(stack.cards.list, 2) == 'C');
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Peek()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Peek");

        CardStackAuto stack;

        CardStackPush(stack, 'P');
        CardStackPush(stack, 'E');
        CardStackPush(stack, 'E');
        CardStackPush(stack, 'K');

        TEST_CASE_ASSERT(CardStackPeek(stack) == 'K');
        TEST_CASE_ASSERT(CardStackPeek(stack) == 'K');
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Push()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Empiler avec capacite nulle");

        CardStackAuto stack;

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');

        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        TEST_CASE_ASSERT(CardStackPeek(stack) == 'C');
        TEST_CASE_ASSERT(ListSize(stack.cards.list) == 3);
    }

    {
        TEST_CASE_ENTER("Empiler avec capacite non nulle");

        CardStackAuto stack(4);

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');
        CardStackPush(stack, 'D');

        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        TEST_CASE_ASSERT(stack.cards.list.capacity == 4);

        CardStackPush(stack, 'E');

        TEST_CASE_ASSERT(stack.cards.list.capacity > 4);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Pop()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Pop");

        CardStackAuto stack;

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');
        CardStackPush(stack, 'D');

        CardStackPop(stack);
        CardStackPop(stack);
        CardStackPop(stack);
        CardStackPop(stack);

        TEST_CASE_ASSERT(IsEmpty(stack));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Empty()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        CardStackAuto stack;
        TEST_CASE_ASSERT(IsEmpty(stack));
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        CardStackAuto stack(10);
        TEST_CASE_ASSERT(IsEmpty(stack));
    }

    {
        TEST_CASE_ENTER("Ajout");

        CardStackAuto stack(10);
        CardStackPush(stack, 'A');
        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_COMPONENT_CardStack()
{
    TEST_COMPONENT_ENTER();

    TEST_CardStack_AssignList();
    TEST_CardStack_Peek();
    TEST_CardStack_Push();
    TEST_CardStack_Pop();
    TEST_CardStack_Empty();

    TEST_COMPONENT_LEAVE();
}