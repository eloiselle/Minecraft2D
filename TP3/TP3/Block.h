/*****************************************************************************
File  : Block.h
Author: Anthony Cote
Date  : 2018-05-13
Goal  : Bloc a chaque espace dans la grille
******************************************************************************/
#pragma once
#include "pch.h"

using namespace std;

const enum BLOCK_TYPE { EMPTY_BLOCK = 0, SOFT_BLOCK, HARD_BLOCK, VISITED, INVALID_BLOCK };


class Block
{
private:
    BLOCK_TYPE _type;                                       // Type de block
    unsigned int _version;                                  // Version de l'image a utiliser

public:
    Block() : _type(EMPTY_BLOCK), _version(0) {};           // Constructor

    unsigned int getVersion();                              // Retourne la version
    BLOCK_TYPE getType();                                   // Retourne le type de block

    void set(BLOCK_TYPE type, unsigned int version = -1);   // Set
    BLOCK_TYPE operator=(BLOCK_TYPE c);                     // Assigne
    
};

istream& operator>>(istream& is, Block& b);
