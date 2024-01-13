/*!
 * @file Definitions.hpp
 * @brief Définitions des constantes, types et énumérations relatives au jeu
 */

#ifndef LEXICON_DEFINITIONS_HPP
#define LEXICON_DEFINITIONS_HPP


//
// Renvoie la plus petite valeur entre X et Y
//
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


//
// chemin relatif du fichier dictionnaire à utiliser
//
#define DICTIONARY_PATH "ods4.txt"


//
// Récupère la position (à partir de 0) d'une lettre dans l'alphabet
// 'A' -> 0
// 'B' -> 1
// ...
// 'Y' -> 24
// 'Z' -> 25
//
#define CARD_NO(c) ((c) - 'A')

//
// Récupère la valeur correspondant à une position (à partir de 0) dans l'alphabet
// 0 -> 'A'
// 1 -> 'B'
// ...
// 24 -> 'Y'
// 25 -> 'Z'
//
#define CARD_VALUE(cardNo) ((cardNo) + 'A')


enum
{
    MIN_PLAYER_COUNT = 2,       // Nombre de joueurs minimum
    MAX_PLAYER_COUNT = 4,       // Nombre de joueurs maximum

    CARDS_COUNT_VALUES = 26,    // Nombre de cartes différentes dans un paquet du jeu
    CARDS_COUNT_GAME = 51,      // Nombre de cartes totales dans un paquet du jeu
    CARDS_COUNT_PLAYER = 10,    // Nombre de cartes distribuées à un joueur

    DICTIONARY_WORD_COUNT = 369085,  // Le dictionnaire contient 369085 mots
    DICTIONARY_MAX_WORD_SIZE = 15,   // Le(s) plus grand(s) mot(s) du dictionnaire ont une taille de 15 caractères

    MAX_COMMAND_LENGTH = 64,         // La taille maximale (sans le 0 terminal) d'une commande entrée par le joueur
    MAX_COMMAND_WORD_LENGTH = DICTIONARY_MAX_WORD_SIZE,  // La taille maximale d'un mot donné en paramètre à une commande

    INVALID_WORD_PENALTY = 3,   // Nombre de points de pénalité attribués à un joueur lorsque le mot entré est invalide

    SCORE_TO_LOSE = 100  // Chaque joueur ayant un score supérieur ou égale à cette valeur après un tour est éliminé
};

//
// Une carte est représentée par un caractère pour le moment
//
typedef char Card;


//
// Les valeurs que peuvent prendre chaque commande entrée par l'utilisateur
//
enum Commands
{
    TALON    = 'T',
    EXPOSED  = 'E',
    PLACE    = 'P',
    REPLACE  = 'R',
    COMPLETE = 'C'
};


#endif //LEXICON_DEFINITIONS_HPP
