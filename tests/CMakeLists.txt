cmake_minimum_required(VERSION 3.23)
project(IUT_Projet2_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(IUT_Projet2_tests
        TestsMain.cpp

        ../cardlist.cpp
        ../cardlist.hpp

        ../wordlist.cpp
        ../wordlist.hpp

        ../cardstack.cpp
        ../cardstack.hpp

        ../gamelogic.cpp
        ../gamelogic.hpp

        ../gameinterface.cpp
        ../gameinterface.hpp

        ../players.cpp
        ../players.hpp

        TestCardList.cpp
        TestCardList.hpp

        TestWordList.cpp
        TestWordList.hpp

        TestCardStack.cpp
        TestCardStack.hpp

        TestGame.cpp
        TestGame.hpp

        AutoDestructors.hpp
        )
