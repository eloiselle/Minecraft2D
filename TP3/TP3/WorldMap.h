/*****************************************************************************
File  : Labyrinthe.cpp
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Wrapper de Map<char> qui contient les positions de depart et arrivee
        ainsi que la lecture de fichier de labyrinthe
******************************************************************************/
#pragma once
#include "pch.h"

#include "ResizableMap.HPP"
#include "MagnetPosition.h"
#include "FileOpener.h"
#include "Block.h"
using namespace std;

constexpr int NBR_EMPTY_LINE_ON_TOP = 5;

class WorldMap : public ResizableMap<Block>, FileOpener {
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

    void randomize();                           //
    void randomizeLine(int line);               //
    void fillLine(int line, BLOCK_TYPE bt);     //

    void randomizeLineVersion(int line);

    bool isTraversable(pixel_t x, pixel_t y);   //
    bool isTraversable(tile_t x, tile_t y);     //
    bool isTraversable(MagnetPosition& mp);     //

    bool isDestructible(pixel_t x, pixel_t y);  //
    bool isDestructible(tile_t x, tile_t y);    //
    bool isDestructible(MagnetPosition & mp);   //

    void readGrid(istream& is = cin);           // Lit la matrice de la map dans le flux
    bool readFile(const char* nomFichier);      // Lit la map
    bool blockIsTraversable(Block& cm);         //
    bool blockIsDestructible(Block& cm);        //
};
