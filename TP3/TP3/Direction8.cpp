#include "Direction8.h"


// Constructeur avec x et y
Direction8::Direction8(float x, float y)
{
    _grid = -1;
    _deltaX = x;
    _deltaY = y;
}


int Direction8::getValue(){    return _grid;}
float Direction8::getX(){    return _deltaX;}
float Direction8::getJumpY(){    return _deltaY;}

// Modifie la direction a partir de l'array par défaut de direction
void Direction8::setDirection(int dir)
{
    _deltaX = D8_x[dir];
    _deltaY = D8_y[dir];
    _grid = dir;
}

// Copie la direction
void Direction8::setDirection(Direction8& dir)
{
    _deltaX = dir._deltaX;
    _deltaY = dir._deltaY;
    _grid = dir._grid;
}