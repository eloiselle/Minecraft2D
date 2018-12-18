/*****************************************************************************
File  : FixedGrid.h
Author: Anthony Côté
Date  : 2018-11-10
Goal  : Grille templated qui représente une matrice
        La taille est defini en template donc elle n'est pas modifiable
******************************************************************************/
#pragma once
#include "pch.h"

using namespace std;

template <class T, unsigned int NB_LINE, unsigned int NB_COL>
class FixedGrid
{
private:
    T _grid[NB_LINE][NB_COL];                   // Matrice 2D de T

public:
    FixedGrid() { init(); };                    // Constructeur
    void init();                                // Initialize

    // Get-set
    T getElement(int col, int line)const;       // Retourne l'element a la position
    void setElement(int col, int line, const T& nouvelleValeur);    // Change l'element

    // Methodes
    void randomize();                           // Crée une map aléatoire
    void rempliLesBordures();                   // Fait le countour de la grille

    // IO
    void affiche()const;                        // Affichage
    void saveToFile(string fileName)const;      // Sauvegarde la grille dans un fichier
    void loadFromFile(string fileName);         // Load la grille d'un fichier
};

// Initialize la map
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::init()
{
    randomize();
}

// Retourne la valeur dans la grille a la position
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
T FixedGrid<T, NB_LINE, NB_COL>::getElement(int col, int line)const
{
    assert(col >= 0);
    assert(line >= 0);
    assert(line < NB_LINE);
    assert(col < NB_COL);

    return _grid[col][line].getType();
}

// Change la valeur dans la grille a la position
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::setElement(int col, int line, const T& nouvelleValeur)
{
    assert(nouvelleValeur >= 0);
    _grid[col][line].set(nouvelleValeur);
}

// Genere un map au hasard
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::randomize()
{
    rempliLesBordures();

    // Rempli la map
    for (size_t x = 1; x < MAP_SIZE_X - 1; x++)
    {
        for (size_t y = 1; y < MAP_SIZE_Y - 1; y++)
        {
            //
        }
    }
}

// Rempli les 4 bordures de la map avec des rochers
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::rempliLesBordures()
{
    // Rempli les bordures horizontales
    for (size_t c = 0; c < NB_COL; c++)
    {
        _grid[c][0].set(Block::HARD_BLOCK);
        _grid[c][NB_COL - 1].set(Block::HARD_BLOCK);
    }
    // Rempli les bordures verticales
    for (size_t l = 0; l < NB_LINE; l++)
    {
        _grid[0][l].set(Block::HARD_BLOCK);
        _grid[NB_LINE - 1][l].set(Block::HARD_BLOCK);
    }
}

// Affiche la map dans la fenetre avec les textures
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::affiche()const
{
    //SDL_Rect currentTilePosition;

    for (int l = 0; l < NB_LINE; l++)
    {
        for (int c = 0; c < NB_COL; c++)
        {
            //currentTilePosition.x = i * TILE_SIZE;
            //currentTilePosition.y = j * TILE_SIZE;

            //switch (_value[i][j].getType())
            //{
            //case Block::HARD_BLOCK:
            //    //
            //    break;
            //case Block::SOFT_BLOCK:
            //    //
            //    break;
            //case Block::NO_BLOCK:
            //    //
            //    break;
            //case Block::POWERUP:
            //    //
            //    break;
            //}
        }
    }
}

// sauvegarde une map dans un fichier
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::saveToFile(string fileName)const
{
    ofstream ofs(fileName);

    for (size_t c = 0; c < NB_COL; c++)
    {
        for (size_t l = 0; l < NB_LINE; l++)
        {
            ofs << _grid[c][l].getType();
        }
    }
}

// load
template <class T, unsigned int NB_LINE, unsigned int NB_COL>
void FixedGrid<T, NB_LINE, NB_COL>::loadFromFile(string fileName)
{
    ifstream ifs(fileName);

    for (int c = 0; c < NB_COL; c++)
    {
        for (int l = 0; l < NB_LINE; l++)
        {
            char t;
            ifs >> t;
            _grid[c][l].set(t);
        }
    }
}