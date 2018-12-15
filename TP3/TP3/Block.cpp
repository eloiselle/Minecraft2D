#pragma once

#include "Block.h"

BLOCK_TYPE Block::getType() { return _type; }
unsigned int Block::getVersion() { return _version; }

void Block::setType(BLOCK_TYPE type) { _type = type; }
void Block::setVersion(int version) { _version = version; }

void Block::setRandomVersion()
{
    if (_type == INVALID_BLOCK)
        _version = 0;
    else
        _version = rand() % NB_VERSION_BLOCK;
}

// Change le type de block et choisi une version au hasard
void Block::set(BLOCK_TYPE type, unsigned int version)
{
    _type = type;
    _version = version;
}


// Operateur = pour assignation
BLOCK_TYPE Block::operator=(BLOCK_TYPE c)
{
    setType(c);
    setRandomVersion();
    return c;
}

istream& operator>>(istream& is, Block& b)
{
    char c;
    is >> c;
    b.setType(static_cast<BLOCK_TYPE>(c));
    return is;
}