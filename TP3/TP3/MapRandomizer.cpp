#include "MapRandomizer.h"


MapRandomizer::MapRandomizer(WorldMap& wm) : flip(true)
{
    nbCol = wm.nbCol();
    nbLine = wm.nbLine();

    randomizePure();

    //update(10);

    //
    for (size_t c = 0; c < nbCol; c++)
    {
        for (size_t l = 0; l < nbLine; l++)
        {
            //wm.at(l, c).set(_world[l][c][0]);
            //wm.at(l, c).set(static_cast<BLOCK_TYPE>(((l+c)%2)+48));
        }
    }
}


void MapRandomizer::randomizePure(bool flip)
{
    for (char l = 0; l < nbCol; l++)
    {
        for (char c = 0; c < nbLine; c++)
        {
            BLOCK_TYPE bl[5] = { EMPTY_BLOCK , SOFT_BLOCK};
            int type = rand() % 2;
            _world[l][c][flip] = bl[type];
        }
    }
}

//void MapRandomizer::print()
//{
//    char charToShow[2] = { ' ', '#' };
//
//    for (char i = 0; i < HEIGHT; i++) {
//        for (char j = 0; j < WIDTH; j++) {
//            cout << charToShow[world[i][j][flip]];
//        }
//        cout << endl;
//    }
//
//    cout << endl;
//}

void MapRandomizer::update(unsigned int iterations)
{
    for (size_t i = 0; i < iterations; i++)
    {
        for (int l = 0; l < nbLine; l++)
        {
            for (int c = 0; c < nbCol; c++)
            {
                _world[l][c][!flip] = getBlockType(l, c);
            }
        }
        flip = !flip;
    }
}

int MapRandomizer::getVoisins(int line, int col)
{
    int voisins = 0;

    // Calcule le nombres de voisin
    for (char l = line - 1; l <= line + 1; l++) // TODO utiliser MIN/MAX pour les limites de boucle
    {
        for (char c = col - 1; c <= col + 1; c++)
        {
            if (l != line || c != col) // si on se ne se regarde pas soi meme
            {
                if (l > -1 && l < nbLine && c > -1 && c < nbCol) // si pas a l'exterieur de la map
                {
                    if (_world[l][c][flip] == SOFT_BLOCK)
                    {
                        voisins++;
                    }
                }
            }
        }
    }
    return voisins;
}

BLOCK_TYPE MapRandomizer::getBlockType(int line, int col)
{
    int voisins = getVoisins(line, col);
    BLOCK_TYPE type = _world[line][col][flip];

    if (type == SOFT_BLOCK) 
    {
        switch (voisins)
        {
        case 0: case 1: case 2: case 3: case 4:
            return SOFT_BLOCK;                           break;
        case 5: case 6: case 7: case 8: case 9:
            return EMPTY_BLOCK;                           break;
        default:
            return type;
        }
    }
    else if(type == EMPTY_BLOCK)
    {
        switch (voisins)
        {
        case 0: case 1: case 2: case 3: case 4:
            return EMPTY_BLOCK;                           break;
        case 5: case 6: case 7: case 8: case 9:
            return SOFT_BLOCK;                           break;
        default:
            return type;
        }
    }
}

