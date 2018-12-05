
#include "Block.h"

BLOCK_TYPE Block::getType() { return _type; }
unsigned int Block::getVersion() { return _version; }


// Change le type de block et choisi une version au hasard
void Block::set(BLOCK_TYPE type, unsigned int version)
{
    _type = type;

    if (version == -1)
    {
        // Choisi une version de l'image au hasard
        switch (_type)
        {
        case EMPTY_BLOCK:       _version = rand() % 4;      break;
        case HARD_BLOCK:        _version = rand() % 4;      break;
        case SOFT_BLOCK:        _version = rand() % 4;      break;
        default:
            _type = INVALID_BLOCK; _version = 0;               break;
        }
    }
}


// Operateur = pour assignation
BLOCK_TYPE Block::operator=(BLOCK_TYPE c)
{
    set(c);
    return c;
}

istream& operator>>(istream& is, Block& b)
{
    char c;
    is >> c;
    b.set(static_cast<BLOCK_TYPE>(c));
    return is;
}