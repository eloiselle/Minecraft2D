/*****************************************************************************
File  : Block.h
Author: Anthony Cote
Date  : 2018-05-13
Goal  : Bloc a chaque espace dans la grille
******************************************************************************/
#pragma once
#include "pch.h"
using namespace std;

enum BLOCK_TYPE { HARD_BLOCK = '#', NO_BLOCK = '.', SOFT_BLOCK = 'o', POWERUP = 'P' };

class Block
{
private:
    BLOCK_TYPE _type;                               // Type de block
    int _version;                                   // Version de l'image a utiliser

public:
    Block() :_type(NO_BLOCK), _version(0) {};       // Constructor

    int getVersion();                               // Retourne la version
    BLOCK_TYPE getType();                           // Retourne le type de block

    void set(BLOCK_TYPE type, int version = -1);    // Set
    BLOCK_TYPE operator=(BLOCK_TYPE c);             // Assigne
};

// Change le type de block et choisi une version au hasard
void Block::set(BLOCK_TYPE type, int version)
{
    _type = type;

    if (version == -1)
    {
        // Choisi une version de l'image au hasard
        switch (_type)
        {
        case NO_BLOCK:          _version = rand() % 8;      break;
        case HARD_BLOCK:        _version = rand() % 11;     break;
        case SOFT_BLOCK:        _version = rand() % 15;     break;
        case POWERUP:           _version = 0;               break;
        default:
            _type = HARD_BLOCK; _version = 0;               break;
        }
    }
}

// Get type de block
BLOCK_TYPE Block::getType()
{
    return _type;
}

// Get version du block
int Block::getVersion()
{
    return _version;
}

// Operateur = pour assignation
BLOCK_TYPE Block::operator=(BLOCK_TYPE c)
{
    set(c);
    return c;
}