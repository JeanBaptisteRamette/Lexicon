#ifndef IUT_PROJET2_DEFINITIONS_HPP
#define IUT_PROJET2_DEFINITIONS_HPP





#define DICTIONARY_PATH "ods4.txt"


enum
{
    MIN_PLAYER_COUNT = 2,
    MAX_PLAYER_COUNT = 4,

    CARDS_COUNT_VALUES = 26,    // Nombre de cards différentes dans un paquet du jeu
    CARDS_COUNT_GAME = 51,      // Nombre de cards totales dans un paquet du jeu
    CARDS_COUNT_PLAYER = 10,    // Nombre de cards distribuées à un joueur

    DICTIONARY_WORD_COUNT = 369085,
    DICTIONARY_MAX_WORD_SIZE = 15,

    MAX_COMMAND_LENGTH = 32,
    MAX_COMMAND_WORD_LENGTH = DICTIONARY_MAX_WORD_SIZE,

    INVALID_WORD_PENALTY = 3,

    MAXIMUM_QUALIFIED_SCORE = 100
};

typedef char Card;


enum Command
{
    TALON    = 'T',
    EXPOSED  = 'E',
    PLACE    = 'P',
    REPLACE  = 'R',
    COMPLETE = 'C'
};


#endif //IUT_PROJET2_DEFINITIONS_HPP
