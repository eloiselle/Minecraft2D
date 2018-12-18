#pragma once
#include "WorldMap.h"

using namespace std;

// Retourne les positions de depart et d'arrivee
int WorldMap::xDepart() const { return _xDepart; }
int WorldMap::yDepart() const { return _yDepart; }
int WorldMap::xFin() const { return _xFin; }
int WorldMap::yFin() const { return _yFin; }

void WorldMap::randomize()
{
    //assert(_map != nullptr);
    //assert(_nbL > 0);
    //assert(_nbC > 0);

    resize(25, 32);

    fillLine(0, HARD_BLOCK); // Premiere ligne de HARD_BLOCK pour prevenir des bug
    randomizeLineVersion(0);

    // Quelques premieres lignes vides
    for (size_t l = 1; l < NBR_EMPTY_LINE_ON_TOP; l++)
    {
        fillLine(l, EMPTY_BLOCK);
        randomizeLineVersion(l);
    }
    // On remplace les characteres par celui de l'entree
    for (int l = NBR_EMPTY_LINE_ON_TOP; l < _nbL; l++)      // Lignes
    {
        randomizeLine(l);
    }

    // Rempli les bordures
    for (size_t l = 0; l < _nbL; l++)
    {
        _map[l][0].setType(HARD_BLOCK);
        _map[l][0].setRandomVersion();
        _map[l][_nbC - 1].setType(HARD_BLOCK);
        _map[l][_nbC - 1].setRandomVersion();
    }
}

void WorldMap::randomizeLine(int line)
{
    BLOCK_TYPE blockByID[6] = {
        EMPTY_BLOCK, EMPTY_BLOCK, EMPTY_BLOCK,
        SOFT_BLOCK, SOFT_BLOCK,
        HARD_BLOCK };

    for (int c = 1; c < _nbC - 1; c++)  // Colonnes
    {
        _map[line][c].setType(blockByID[rand() % 6]);
        _map[line][c].setRandomVersion();
    }

    _map[line][0].setType(HARD_BLOCK);
    _map[line][0].setRandomVersion();
    _map[line][_nbC - 1].setType(HARD_BLOCK);
    _map[line][_nbC - 1].setRandomVersion();
}

void WorldMap::fillLine(int line, BLOCK_TYPE bt)
{
    for (int c = 1; c < _nbC - 1; c++)  // Colonnes
    {
        _map[line][c].setType(bt);
    }

    _map[line][0].setType(HARD_BLOCK);
    _map[line][_nbC - 1].setType(HARD_BLOCK);
}

void WorldMap::randomizeLineVersion(int line)
{
    for (int c = 0; c < _nbC - 1; c++)  // Colonnes
    {
        _map[line][c].setRandomVersion();
    }
}

void WorldMap::readGrid(istream& is)
{
    assert(_map != nullptr);
    assert(_nbL > 0);
    assert(_nbC > 0);

    // On remplace les characteres par celui de l'entree
    for (int l = 0; l < _nbL; l++)      // Lignes
    {
        for (int c = 0; c < _nbC; c++)  // Colonnes
        {
            int val;
            is >> val;          // Remplace le char suivant
            _map[l][c].setType(static_cast<BLOCK_TYPE>(val));
            _map[l][c].setRandomVersion();
        }
    }
}

// Lecture du fichier et extrait la map
bool WorldMap::readFile(const char* nomFichier)
{
    openFile(nomFichier);

    if (isValidFile())
    {
        setName(nomFichier);

        // Lecture de la taille de la map
        int nbL, nbC;
        _ifs >> nbL >> nbC;

        resize(nbL, nbC);

        readGrid(_ifs);

        // Prend les positions de depart et d'arrivee
        _ifs >> _xDepart >> _yDepart >> _xFin >> _yFin;

        _ifs.close();
        return true;
    }
    else
    {
        cout << "Le fichier '" << nomFichier << "' n'existe pas.";
        return false;
    }
}

bool WorldMap::blockIsTraversable(Block& cm) { return cm.getType() == EMPTY_BLOCK; }
bool WorldMap::blockIsDestructible(Block& cm) { return cm.getType() == SOFT_BLOCK; }

bool WorldMap::isTraversable(pixel_t x, pixel_t y)
{
    MagnetPosition mp;
    mp.setPositionExact(x, y);
    return blockIsTraversable(at(mp.getGridLine(), mp.getGridCol()));
}

bool WorldMap::isTraversable(tile_t x, tile_t y)
{
    return blockIsTraversable(at(y, x));
}

bool WorldMap::isTraversable(MagnetPosition & mp)
{
    return blockIsTraversable(at(mp.getGridLine(), mp.getGridCol()));
}

bool WorldMap::isDestructible(pixel_t x, pixel_t y)
{
    MagnetPosition mp;
    mp.setPositionExact(x, y);
    return blockIsDestructible(at(mp.getGridLine(), mp.getGridCol()));
}

bool WorldMap::isDestructible(tile_t x, tile_t y)
{
    return blockIsDestructible(at(y, x));
}

bool WorldMap::isDestructible(MagnetPosition & mp)
{
    return blockIsDestructible(at(mp.getGridLine(), mp.getGridCol()));
}

//char& WorldMap::at(MagnetPosition & mp)const
//{
//    assert(_map != nullptr);
//    assert(mp.getGridLine() > 0);
//    assert(mp.getGridCol() > 0);
//    assert(mp.getGridLine() < _nbL);
//    assert(mp.getGridCol() < _nbC);
//
//    return _map[mp.getGridLine()][mp.getGridCol()]; // Retourne l'element pour acceder ou modifier.
//}