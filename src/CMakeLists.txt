cmake_minimum_required(VERSION 3.22.1)
project(IUT_Projet2)

set(CMAKE_CXX_STANDARD 20)

add_executable(IUT_Projet2
        main.cpp

        Game/Player.cpp
        Game/Player.hpp

        Game/Players.cpp
        Game/Players.hpp

        Game/Containers/CardList.cpp
        Game/Containers/CardList.hpp

        Game/Logic.cpp
        Game/Logic.hpp

        Game/Interface.cpp
        Game/Interface.hpp

        Game/Containers/CardStack.cpp
        Game/Containers/CardStack.hpp

        Game/Containers/WordList.cpp
        Game/Containers/WordList.hpp

        Game/GameData.cpp
        Game/GameData.hpp)