/*****************************************************************************
File  : Direction.h
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Représente une Direction divisé en 8 valeur (0-7) en sens horaire
******************************************************************************/

#pragma once
#include "pch.h"

#include "Const.h"
#include "Position.h"



class Direction8
{
public:
    Direction8()
        : _grid(DOWN), _deltaX(0), _deltaY(1) {}; // Constructeur
    Direction8(float x, float y);

    // Get
    int getValue();
    float getX();
    float getJumpY();

    // Set
    void setDirection(int dir);
    void setDirection(Direction8& dir);

protected:
    int _grid;
    float _deltaX;
    float _deltaY;
};
