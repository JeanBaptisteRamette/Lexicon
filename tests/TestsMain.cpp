#include "TestCardList.hpp"
#include "TestWordList.hpp"
#include "TestCardStack.hpp"
#include "TestGame.hpp"


int main()
{
    TEST_COMPONENT_CardList();
    TEST_COMPONENT_WordList();
    TEST_COMPONENT_CardStack();
    TEST_COMPONENT_Game();

    return 0;
}