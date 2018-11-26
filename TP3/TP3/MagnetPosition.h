/******************************************************************************
File  : MagnetPosition.h
Author: Anthony Cote
Date  : 2018-04-30
Goal  : Ensemble de deux positions qui sont coordonnées
        L'une pour la position exacte et une pour la position dans une grille
******************************************************************************/

#pragma once
#include "pch.h"

#include "Const.h"

class MagnetPosition
{
protected:

    pixel_t _exactX;                // La colonne dans la grille
    pixel_t _exactY;                // La ligne dans la grille
    tile_t _gridC;                  // La position x exacte
    tile_t _gridL;                  // La position y exacte

public:
    MagnetPosition(pixel_t exactX = 0, pixel_t exactY = 0, tile_t gridC = 0, tile_t gridL = 0)
        : _exactX(exactX), _exactY(exactY), _gridC(gridC), _gridL(gridL) {};  // Constructeur

    // Get
    tile_t getGridCol() { return _gridC; };         // Get la colonne dans la grille
    tile_t getGridLine() { return _gridL; };        // Get la ligne dans la grille
    pixel_t getExactX() { return _exactX; };        // Get la position x exacte
    pixel_t getExactY() { return _exactY; };        // Get la position y exacte

    // Set
    void setPosition(MagnetPosition& mp);           // Copie une MagnetPosition
    void setPositionInGrid(tile_t x, tile_t y);     // Change la position dans la grille
    void setPositionExact(pixel_t x, pixel_t y);    // Change la position exacte
    void move(pixel_t x, pixel_t y);                // Deplacement a partir de la position actuelle

    void updateGridPosition();  // Met a jour la position dans la grille selon la position exacte
    bool isGridCentered();      // Vérifi si est au centre de la case pour lancer AI
};
