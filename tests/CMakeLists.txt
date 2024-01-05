cmake_minimum_required(VERSION 3.23)
project(IUT_Projet2_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(IUT_Projet2_tests
        TestsMain.cpp
        Tests.hpp

        ../src/Game/Containers/CardList.cpp
        ../src/Game/Containers/CardList.hpp

        ../src/Game/Containers/WordList.cpp
        ../src/Game/Containers/WordList.hpp

        ../src/Game/Containers/CardStack.cpp
        ../src/Game/Containers/CardStack.hpp

        ../src/Game/GameData.cpp
        ../src/Game/GameData.hpp

        ../src/Game/Logic.cpp
        ../src/Game/Logic.hpp

        ../src/Game/Interface.cpp
        ../src/Game/Interface.hpp

        ../src/Game/Player.cpp
        ../src/Game/Player.hpp

        ../src/Game/Players.cpp
        ../src/Game/Players.hpp

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
