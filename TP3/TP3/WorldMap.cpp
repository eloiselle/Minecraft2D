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
