#include "WorldMap.h"

using namespace std;

// Retourne les positions de depart et d'arrivee
int WorldMap::xDepart() const { return _xDepart; }
int WorldMap::yDepart() const { return _yDepart; }
int WorldMap::xFin() const { return _xFin; }
int WorldMap::yFin() const { return _yFin; }

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

        // Lecture de la grille
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


bool WorldMap::isTraversable(pixel_t x, pixel_t y)
{
    MagnetPosition mp;
    mp.setPositionExact(x, y);
    char cm = at(mp.getGridLine(), mp.getGridCol());
    return cm == EMPTY_BLOCK || cm == HARD_BLOCK;
}

bool WorldMap::isTraversable(tile_t x, tile_t y)
{
    char cm = at(y, x);
    return cm == EMPTY_BLOCK || cm == HARD_BLOCK;
}

bool WorldMap::isTraversable(MagnetPosition & mp)
{
    char cm = at(mp.getGridLine(), mp.getGridCol());
    return cm == EMPTY_BLOCK || cm == HARD_BLOCK;
}

bool WorldMap::isDestructible(pixel_t x, pixel_t y)
{
    MagnetPosition mp;
    mp.setPositionExact(x, y);
    char cm = at(mp.getGridLine(), mp.getGridCol());
    return cm == EMPTY_BLOCK;
}

bool WorldMap::isDestructible(tile_t x, tile_t y)
{
    char cm = at(y, x);
    return cm == EMPTY_BLOCK;
}

bool WorldMap::isDestructible(MagnetPosition & mp)
{
    char cm = at(mp.getGridLine(), mp.getGridCol());
    return cm == EMPTY_BLOCK;
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
