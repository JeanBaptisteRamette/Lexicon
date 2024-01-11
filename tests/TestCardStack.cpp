#include "TestCardStack.hpp"
#include "Tests.hpp"
#include "../src/Game/Containers/CardStack.hpp"


void TEST_CardStack_Peek()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Peek");

        CardStack stack = CardStackCreate();

        CardStackPush(stack, 'P');
        CardStackPush(stack, 'E');
        CardStackPush(stack, 'E');
        CardStackPush(stack, 'K');

        TEST_CASE_ASSERT_EQUAL(CardStackPeek(stack), 'K');
        TEST_CASE_ASSERT_EQUAL(CardStackPeek(stack), 'K');

        CardStackDestroy(stack);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Push()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Empiler avec capacite nulle");

        CardStack stack = CardStackCreate();

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');

        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        TEST_CASE_ASSERT_EQUAL(CardStackPeek(stack), 'C');
        TEST_CASE_ASSERT_EQUAL(ListSize(stack.list), 3);

        CardStackDestroy(stack);
    }

    {
        TEST_CASE_ENTER("Empiler avec capacite non nulle");

        CardStack stack = CardStackCreate(4);

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');
        CardStackPush(stack, 'D');

        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        TEST_CASE_ASSERT_EQUAL(stack.list.capacity, 4);

        CardStackPush(stack, 'E');

        TEST_CASE_ASSERT_TRUE(stack.list.capacity > 4);

        CardStackDestroy(stack);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Pop()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Pop");

        CardStack stack = CardStackCreate();

        CardStackPush(stack, 'A');
        CardStackPush(stack, 'B');
        CardStackPush(stack, 'C');
        CardStackPush(stack, 'D');

        CardStackPop(stack);
        CardStackPop(stack);
        CardStackPop(stack);
        CardStackPop(stack);

        TEST_CASE_ASSERT_TRUE(IsEmpty(stack));

        CardStackDestroy(stack);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_CardStack_Empty()
{
    TEST_FUNCTION_ENTER();

    {
        TEST_CASE_ENTER("Capacite nulle");

        CardStack stack = CardStackCreate();
        TEST_CASE_ASSERT_TRUE(IsEmpty(stack));
        CardStackDestroy(stack);
    }

    {
        TEST_CASE_ENTER("Capacite non-nulle");

        CardStack stack = CardStackCreate(10);
        TEST_CASE_ASSERT_TRUE(IsEmpty(stack));
        CardStackDestroy(stack);
    }

    {
        TEST_CASE_ENTER("Ajout");

        CardStack stack = CardStackCreate(10);
        CardStackPush(stack, 'A');
        TEST_CASE_ASSERT_FALSE(IsEmpty(stack));
        CardStackDestroy(stack);
    }

    TEST_FUNCTION_LEAVE();
}

void TEST_COMPONENT_CardStack()
{
    TEST_COMPONENT_ENTER();

    TEST_CardStack_Peek();
    TEST_CardStack_Push();
    TEST_CardStack_Pop();
    TEST_CardStack_Empty();

    TEST_COMPONENT_LEAVE();
}