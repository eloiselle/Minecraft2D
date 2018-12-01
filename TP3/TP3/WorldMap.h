/*****************************************************************************
File  : Labyrinthe.cpp
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Wrapper de Map<char> qui contient les positions de depart et arrivee
        ainsi que la lecture de fichier de labyrinthe
******************************************************************************/
#pragma once
#include "pch.h"

#include "Const.h"
#include "ResizableMap.HPP"
#include "MagnetPosition.h"
#include "FileOpener.h"
using namespace std;

enum CHAR_MAP { EMPTY_BLOCK = '0', SOFT_BLOCK, HARD_BLOCK, VISITED, CHECKPOINT };    // Type de cases

class WorldMap : public ResizableMap<char>, FileOpener {
private:
    // Positions de depart et d'arrivee
    int _xDepart;           // Valeur X de depart
    int _yDepart;           // Valeur Y de depart
    int _xFin;              // Valeur X d'arrivee
    int _yFin;              // Valeur Y d'arrivee

public:
    WorldMap() : _xDepart(0), _yDepart(0), _xFin(0), _yFin(0) {};   // Constructeur

    int xDepart()const;    // Retourne la valeur X de depart
    int yDepart()const;    // Retourne la valeur Y de depart
    int xFin()const;       // Retourne la valeur X d'arrivee
    int yFin()const;       // Retourne la valeur Y d'arrivee

    bool isTraversable(pixel_t x, pixel_t y);   //
    bool isTraversable(tile_t x, tile_t y);     //
    bool isTraversable(MagnetPosition& mp);     //

    bool isDestructible(pixel_t x, pixel_t y);

    bool isDestructible(tile_t x, tile_t y);

    bool isDestructible(MagnetPosition & mp);

    //char & at(MagnetPosition & mp) const;

    bool readFile(const char* nomFichier);      // Lit la map
    bool blockIsTraversable(char cm);
    bool blockIsDestructible(char cm);
};
