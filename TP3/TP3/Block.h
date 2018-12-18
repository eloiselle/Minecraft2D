/*****************************************************************************
File  : Block.h
Author: Anthony Cote
Date  : 2018-05-13
Goal  : Bloc a chaque espace dans la grille
******************************************************************************/
#pragma once
#include "pch.h"

#include "Killable.h"

using namespace std;

constexpr int NB_VERSION_BLOCK = 8;                 // Nombre de version de block
const enum BLOCK_TYPE { EMPTY_BLOCK = 0, SOFT_BLOCK, HARD_BLOCK, VISITED, INVALID_BLOCK };

class Block : public Killable
{
private:
    BLOCK_TYPE _type;                               // Type de block
    unsigned int _version;                          // Version de l'image a utiliser

public:
    Block() : _type(EMPTY_BLOCK), _version(0) {};   // Constructor

    BLOCK_TYPE getType()const;                      // Retourne le type de block
    unsigned int getVersion()const;                 // Retourne la version du block
    void setType(BLOCK_TYPE type);                  // Change le type de block
    void setVersion(int version);                   // Choisi la version
    void setRandomVersion();                        // Met une version au hasard

    void set(BLOCK_TYPE type, unsigned int version);// Set
    BLOCK_TYPE operator=(BLOCK_TYPE c);             // Assigne
};

istream& operator>>(istream& is, Block& b);         // Operator d'output
