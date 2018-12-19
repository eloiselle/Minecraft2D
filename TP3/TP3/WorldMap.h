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

constexpr int NBR_EMPTY_LINE_ON_TOP = 12;
constexpr int NBR_GROUND_LINES = 2;

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

	void randomize();                               // Cree une map aleatoire
	void randomizeLine(int line);                   // Met la ligne aleatoire
	void fillLine(int line, BLOCK_TYPE bt);         // Rempli la ligne

	void randomizeLineVersion(int line);            // Met une version de block aleatoire sur toute la ligne

	bool isTraversable(pixel_t x, pixel_t y)const;  // Retourne si le block est traversable
	bool isTraversable(tile_t x, tile_t y)const;    // Retourne si le block est traversable
	bool isTraversable(MagnetPosition& mp)const;    // Retourne si le block est traversable

	bool isDestructible(pixel_t x, pixel_t y)const; // Retourne si le block est destructible
	bool isDestructible(tile_t x, tile_t y)const;   // Retourne si le block est destructible
	bool isDestructible(MagnetPosition & mp)const;  // Retourne si le block est destructible

	void readGrid(istream& is = cin);               // Lit la matrice de la map dans le flux
	bool readFile(const char* nomFichier);          // Lit la map
	bool blockIsTraversable(Block& cm)const;        // Retourne si le block est traversable
	bool blockIsDestructible(Block& cm)const;       // Retourne si le block est destructible
};
