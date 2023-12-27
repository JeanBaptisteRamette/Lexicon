cmake_minimum_required(VERSION 3.23)
project(IUT_Projet2)

set(CMAKE_CXX_STANDARD 20)

add_executable(IUT_Projet2
        main.cpp

        players.hpp
        players.cpp

        cardlist.cpp
        cardlist.hpp

        gamelogic.cpp
        gamelogic.hpp

        gameinterface.cpp
        gameinterface.hpp

        cardstack.cpp
        cardstack.hpp

        wordlist.cpp
        wordlist.hpp

        gamedata.cpp
        gamedata.hpp)
